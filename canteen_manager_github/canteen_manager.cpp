#include "canteen_manager.h"
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QSettings>

canteen_manager::canteen_manager(QWidget *parent)
    : QMainWindow(parent)
    , canteenModel(nullptr)
    , dishModel(nullptr)
    , announcementModel(nullptr)
    , userModel(nullptr)
{
    ui.setupUi(this);
    setupLoginUI();
    
    // 加载默认图片
    defaultDishImage.load(":/images/default_dish.png");
    if (defaultDishImage.isNull()) {
        defaultDishImage = QPixmap(280, 280);
        defaultDishImage.fill(Qt::white);
    }
    
    // 连接食堂管理按钮信号
    connect(ui.addCanteenButton, &QPushButton::clicked, this, &canteen_manager::on_addCanteenButton_clicked);
    connect(ui.editCanteenButton, &QPushButton::clicked, this, &canteen_manager::on_editCanteenButton_clicked);
    connect(ui.deleteCanteenButton, &QPushButton::clicked, this, &canteen_manager::on_deleteCanteenButton_clicked);
    
    // 连接菜品管理按钮信号
    connect(ui.addDishButton, &QPushButton::clicked, this, &canteen_manager::on_addDishButton_clicked);
    connect(ui.editDishButton, &QPushButton::clicked, this, &canteen_manager::on_editDishButton_clicked);
    connect(ui.deleteDishButton, &QPushButton::clicked, this, &canteen_manager::on_deleteDishButton_clicked);
    
    // 连接搜索框信号
    connect(ui.canteenManageSearchEdit, &QLineEdit::textChanged, this, &canteen_manager::updateCanteenSearch);
    connect(ui.dishManageSearchEdit, &QLineEdit::textChanged, this, &canteen_manager::updateDishSearch);
    
    // 连接表格选择信号
    connect(ui.dishManageTableView, &QTableView::clicked, this, &canteen_manager::on_dishManageTableView_clicked);
    
    // 尝试连接数据库
    if (!connectToDatabase()) {
        QMessageBox::critical(this, "错误", "数据库连接失败，请检查配置！");
    }
}

canteen_manager::~canteen_manager()
{
    if (db.isOpen()) {
        db.close();
    }
    
    // 释放模型对象
    delete canteenModel;
    delete dishModel;
    delete announcementModel;
    delete userModel;
}

void canteen_manager::setupLoginUI()
{
    // 设置窗口标题和大小
    setWindowTitle("食堂信息管理系统 - 登录");
    setFixedSize(400, 300);          // 4:3就是好用

    // 隐藏主界面的菜单栏和工具栏
    ui.menuBar->hide();
    ui.mainToolBar->hide();

    // 确保显示登录页面
    ui.stackedWidget->setCurrentWidget(ui.loginPage);

    // 设置密码输入框的回车响应
    connect(ui.passwordEdit, &QLineEdit::returnPressed, this, &canteen_manager::on_loginButton_clicked);
}

void canteen_manager::setupMainUI()
{
    // 设置窗口标题和大小
    setMinimumSize(1024,576);       // 16:9---1280*720||1024*576   4:3--1280*960        向16:9投降

    // 显示菜单栏和工具栏
    ui.menuBar->show();
    ui.mainToolBar->show();

    // 根据用户类型设置不同的界面
    if (userType == "admin") {
        setupAdminUI();
    } else {
        setupUserUI();
    }
}

void canteen_manager::setupAdminUI()
{
    // 设置窗口标题
    setWindowTitle("食堂信息管理系统 - 管理员界面");

    // 显示所有管理功能按钮
    ui.userManageButton->setVisible(true);
    ui.canteenManageButton->setVisible(true);
    ui.menuManageButton->setVisible(true);
    ui.newsManageButton->setVisible(true);

    // 设置按钮使能状态
    ui.userManageButton->setEnabled(true);
    ui.canteenManageButton->setEnabled(true);
    ui.menuManageButton->setEnabled(true);
    ui.newsManageButton->setEnabled(true);
}

void canteen_manager::setupUserUI()
{
    // 设置窗口标题
    setWindowTitle("食堂信息管理系统 - 用户界面");

    // 隐藏管理功能按钮
    ui.userManageButton->setVisible(false);
    
    // 显示查看功能按钮
    ui.canteenManageButton->setVisible(true);
    ui.menuManageButton->setVisible(true);
    ui.newsManageButton->setVisible(true);

    // 启用查看功能按钮
    ui.canteenManageButton->setEnabled(true);
    ui.menuManageButton->setEnabled(true);
    ui.newsManageButton->setEnabled(true);

    // 修改按钮文字，表明是查看功能
    ui.canteenManageButton->setText("食堂信息");
    ui.menuManageButton->setText("菜品信息");
    ui.newsManageButton->setText("查看公告");
}

void canteen_manager::switchToMainUI()
{
    setupMainUI();
    ui.stackedWidget->setCurrentWidget(ui.mainPage);
}

void canteen_manager::switchToLoginUI()
{
    clearLoginInfo();
    setupLoginUI();
    ui.stackedWidget->setCurrentWidget(ui.loginPage);
}

void canteen_manager::clearLoginInfo()
{
    ui.usernameEdit->clear();
    ui.passwordEdit->clear();
    currentUser.clear();
    userType.clear();
}


bool canteen_manager::connectToDatabase()
{
    QSettings settings("config.ini", QSettings::IniFormat);
    QString username = settings.value("Database/Username").toString();
    QString password = settings.value("Database/Password").toString();

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("canteen_db");
    db.setUserName(username);
    db.setPassword(password);
    
    if (!db.open()) {
        qDebug() << "数据库连接失败：" << db.lastError().text();
        return false;
    }
    qDebug() << "数据库连接成功！";
    return true;
}

bool canteen_manager::validateLogin(const QString &username, const QString &password)
{
    QSqlQuery query;
    query.prepare("SELECT user_type FROM users WHERE username = ? AND password = ? AND status = 'active'");
    query.addBindValue(username);
    query.addBindValue(password);
    
    if (!query.exec()) {
        qDebug() << "查询失败：" << query.lastError().text();
        return false;
    }
    
    if (query.next()) {
        userType = query.value(0).toString();
        currentUser = username;
        return true;
    }
    return false;
}

void canteen_manager::on_loginButton_clicked()
{
    QString username = ui.usernameEdit->text().trimmed();
    QString password = ui.passwordEdit->text();
    
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "警告", "用户名和密码不能为空！");
        return;
    }
    
    if (validateLogin(username, password)) {
        QMessageBox::information(this, "成功", "登录成功！");
        switchToMainUI();
    } else {
        QMessageBox::warning(this, "错误", "用户名或密码错误！");
        ui.passwordEdit->clear();
        ui.passwordEdit->setFocus();
    }
}

void canteen_manager::on_exitButton_clicked()
{
    close();
}

// 主界面按钮槽函数
void canteen_manager::on_userManageButton_clicked()
{
    if (userType == "admin") {
        showUserManagePage();
    } else {
        QMessageBox::warning(this, "警告", "您没有权限访问用户管理功能！");
    }
}

void canteen_manager::on_canteenManageButton_clicked()
{
    if (userType == "admin") {
        // 管理员：食堂管理功能
        showCanteenManagePage();
    } else {
        // 普通用户：查看食堂信息
        showCanteenInfo();
    }
}

void canteen_manager::on_menuManageButton_clicked()
{
    if (userType == "admin") {
        // 管理员：菜品管理功能
        showDishManagePage();
    } else {
        // 普通用户：查看菜品信息
        showDishInfo();
    }
}

void canteen_manager::on_newsManageButton_clicked()
{
    if (userType == "admin") {
        // 管理员：公告管理功能
        showAnnouncementManagePage();
    } else {
        // 普通用户：查看公告信息
        showAnnouncementInfo();
    }
}

void canteen_manager::on_logoutButton_clicked()
{
    // 确认是否退出登录
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认退出",
        "确定要退出登录吗？",
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // 切换到登录界面
        switchToLoginUI();
        QMessageBox::information(this, "提示", "已成功退出登录！");
    }
}

// 菜单动作槽函数
void canteen_manager::on_actionLogout_triggered()
{
    on_logoutButton_clicked();
}

void canteen_manager::on_actionExit_triggered()
{
    close();
}

void canteen_manager::showCanteenInfo()
{
    // 初始化模型
    if (!canteenModel) {
        canteenModel = new QSqlQueryModel(this);
    }

    // 使用视图
    canteenModel->setQuery("SELECT * FROM canteens_view");
    
    if (canteenModel->lastError().isValid()) {
        QMessageBox::critical(this, "错误", "获取食堂信息失败：" + canteenModel->lastError().text());
        return;
    }

    // 设置表头
    canteenModel->setHeaderData(0, Qt::Horizontal, "食堂ID");
    canteenModel->setHeaderData(1, Qt::Horizontal, "食堂名称");
    canteenModel->setHeaderData(2, Qt::Horizontal, "简介");
    canteenModel->setHeaderData(3, Qt::Horizontal, "位置");
    canteenModel->setHeaderData(4, Qt::Horizontal, "营业时间");
    canteenModel->setHeaderData(5, Qt::Horizontal, "状态");
    canteenModel->setHeaderData(6, Qt::Horizontal, "评分");

    // 设置表格视图
    ui.canteenTableView->setModel(canteenModel);
    
    // 设置表格样式
    ui.canteenTableView->setStyleSheet(
        "QTableView {"
        "   background-color: white;"
        "   alternate-background-color: #f6f6f6;"
        "   selection-background-color: #0078d7;"
        "   selection-color: white;"
        "   border: 1px solid #c0c0c0;"
        "   gridline-color: #e0e0e0;"
        "}"
        "QHeaderView::section {"
        "   background-color: #f0f0f0;"
        "   color: black;"
        "   padding: 4px;"
        "   border: 1px solid #c0c0c0;"
        "   font-weight: bold;"
        "}"
    );

    // 设置表格属性
    ui.canteenTableView->setAlternatingRowColors(true);
    ui.canteenTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui.canteenTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui.canteenTableView->verticalHeader()->setDefaultSectionSize(30);  // 设置行高
    ui.canteenTableView->verticalHeader()->setVisible(false);  // 隐藏行号
    ui.canteenTableView->horizontalHeader()->setStretchLastSection(true);  // 最后一列自动填充

    // 设置列宽
    ui.canteenTableView->setColumnWidth(0, 60);  // ID列
    ui.canteenTableView->setColumnWidth(1, 100); // 食堂名称
    ui.canteenTableView->setColumnWidth(2, 200); // 简介
    ui.canteenTableView->setColumnWidth(3, 150); // 位置
    ui.canteenTableView->setColumnWidth(4, 100); // 营业时间
    ui.canteenTableView->setColumnWidth(5, 80);  // 状态
    ui.canteenTableView->setColumnWidth(6, 60);  // 评分

    // 切换到食堂信息页面
    ui.contentStackedWidget->setCurrentWidget(ui.canteenPage);
}

void canteen_manager::showDishInfo()
{
    // 初始化模型
    if (!dishModel) {
        dishModel = new QSqlQueryModel(this);
    }

    // 使用视图
    dishModel->setQuery("SELECT * FROM dishes_view");
    
    if (dishModel->lastError().isValid()) {
        qDebug() << "获取菜品信息失败：" << dishModel->lastError().text();
        return;
    }

    // 设置表头
    dishModel->setHeaderData(0, Qt::Horizontal, "菜品ID");
    dishModel->setHeaderData(1, Qt::Horizontal, "所属食堂");
    dishModel->setHeaderData(2, Qt::Horizontal, "菜品名称");
    dishModel->setHeaderData(3, Qt::Horizontal, "描述");
    dishModel->setHeaderData(4, Qt::Horizontal, "价格");
    dishModel->setHeaderData(5, Qt::Horizontal, "类别");
    dishModel->setHeaderData(6, Qt::Horizontal, "是否可用");
    dishModel->setHeaderData(7, Qt::Horizontal, "销量");
    dishModel->setHeaderData(8, Qt::Horizontal, "评分");
    dishModel->setHeaderData(9, Qt::Horizontal, "图片路径");

    // 设置表格视图
    ui.dishTableView->setModel(dishModel);
    
    // 设置表格样式
    ui.dishTableView->setStyleSheet(
        "QTableView {"
        "   background-color: white;"
        "   alternate-background-color: #f6f6f6;"
        "   selection-background-color: #0078d7;"
        "   selection-color: white;"
        "   border: 1px solid #c0c0c0;"
        "   gridline-color: #e0e0e0;"
        "}"
        "QHeaderView::section {"
        "   background-color: #f0f0f0;"
        "   color: black;"
        "   padding: 4px;"
        "   border: 1px solid #c0c0c0;"
        "   font-weight: bold;"
        "}"
    );

    // 设置表格属性
    ui.dishTableView->setAlternatingRowColors(true);
    ui.dishTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui.dishTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui.dishTableView->verticalHeader()->setDefaultSectionSize(30);  // 设置行高
    ui.dishTableView->verticalHeader()->setVisible(false);  // 隐藏行号
    ui.dishTableView->horizontalHeader()->setStretchLastSection(true);  // 最后一列自动填充

    // 设置列宽
    ui.dishTableView->setColumnWidth(0, 60);   // ID列
    ui.dishTableView->setColumnWidth(1, 100);  // 所属食堂
    ui.dishTableView->setColumnWidth(2, 120);  // 菜品名称
    ui.dishTableView->setColumnWidth(3, 200);  // 描述
    ui.dishTableView->setColumnWidth(4, 80);   // 价格
    ui.dishTableView->setColumnWidth(5, 80);   // 类别
    ui.dishTableView->setColumnWidth(6, 80);   // 是否可用
    ui.dishTableView->setColumnWidth(7, 60);   // 销量
    ui.dishTableView->setColumnWidth(8, 60);   // 评分

    // 隐藏图片路径列
    ui.dishTableView->hideColumn(9);

    // 连接选择信号
    connect(ui.dishTableView, &QTableView::clicked, this, &canteen_manager::on_dishTableView_clicked);

    // 清除图片显示
    clearDishImage();

    // 切换到菜品信息页面
    ui.contentStackedWidget->setCurrentWidget(ui.dishPage);
}

void canteen_manager::on_dishTableView_clicked(const QModelIndex &index)
{
    updateDishImage(index);
}

void canteen_manager::updateDishImage(const QModelIndex &index)
{
    // 获取选中行的数据
    int row = index.row();
    QString dishName = dishModel->data(dishModel->index(row, 2)).toString();
    QString price = QString("￥%1").arg(dishModel->data(dishModel->index(row, 4)).toString());
    QString imagePath = dishModel->data(dishModel->index(row, 9)).toString();

    // 更新菜品名称和价格
    ui.dishNameLabel->setText(dishName);
    ui.dishPriceLabel->setText(price);

    // 加载图片
    loadDishImage(imagePath);
}

void canteen_manager::loadDishImage(const QString &imagePath)
{
    if (imagePath.isEmpty()) {
        ui.dishImageLabel->setText("暂无图片");
        return;
    }

    QPixmap image(imagePath);
    if (image.isNull()) {
        ui.dishImageLabel->setText("图片加载失败");
        return;
    }

    // 等比例缩放图片以适应显示区域
    QSize labelSize = ui.dishImageLabel->size();
    image = image.scaled(labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    
    // 设置图片
    ui.dishImageLabel->setPixmap(image);
}

void canteen_manager::clearDishImage()
{
    ui.dishNameLabel->clear();
    ui.dishPriceLabel->clear();
    ui.dishImageLabel->setPixmap(defaultDishImage);
}

void canteen_manager::showAnnouncementInfo()
{
    // 初始化模型
    if (!announcementModel) {
        announcementModel = new QSqlQueryModel(this);
    }

    // 使用视图获取公告信息
    announcementModel->setQuery("SELECT * FROM announcements_view");
    
    if (announcementModel->lastError().isValid()) {
        QMessageBox::critical(this, "错误", "获取公告信息失败：" + announcementModel->lastError().text());
        return;
    }

    // 设置表头
    announcementModel->setHeaderData(0, Qt::Horizontal, "公告ID");
    announcementModel->setHeaderData(1, Qt::Horizontal, "标题");
    announcementModel->setHeaderData(2, Qt::Horizontal, "内容");
    announcementModel->setHeaderData(3, Qt::Horizontal, "发布者");
    announcementModel->setHeaderData(4, Qt::Horizontal, "发布时间");
    announcementModel->setHeaderData(5, Qt::Horizontal, "状态");
    announcementModel->setHeaderData(6, Qt::Horizontal, "更新时间");

    // 设置表格视图
    ui.announcementTableView->setModel(announcementModel);
    
    // 设置表格样式
    ui.announcementTableView->setStyleSheet(
        "QTableView {"
        "   background-color: white;"
        "   alternate-background-color: #f6f6f6;"
        "   selection-background-color: #0078d7;"
        "   selection-color: white;"
        "   border: 1px solid #c0c0c0;"
        "   gridline-color: #e0e0e0;"
        "}"
        "QHeaderView::section {"
        "   background-color: #f0f0f0;"
        "   color: black;"
        "   padding: 4px;"
        "   border: 1px solid #c0c0c0;"
        "   font-weight: bold;"
        "}"
    );

    // 设置表格属性
    ui.announcementTableView->setAlternatingRowColors(true);
    ui.announcementTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui.announcementTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui.announcementTableView->verticalHeader()->setDefaultSectionSize(30);
    ui.announcementTableView->verticalHeader()->setVisible(false);
    ui.announcementTableView->horizontalHeader()->setStretchLastSection(true);

    // 设置列宽
    ui.announcementTableView->setColumnWidth(0, 60);   // ID列
    ui.announcementTableView->setColumnWidth(1, 150);  // 标题
    ui.announcementTableView->setColumnWidth(2, 300);  // 内容
    ui.announcementTableView->setColumnWidth(3, 100);  // 发布者
    ui.announcementTableView->setColumnWidth(4, 150);  // 发布时间
    ui.announcementTableView->setColumnWidth(5, 80);   // 状态
    ui.announcementTableView->setColumnWidth(6, 150);  // 更新时间

    // 隐藏状态列（因为视图中只显示激活的公告）
    ui.announcementTableView->hideColumn(5);

    // 切换到公告信息页面
    ui.contentStackedWidget->setCurrentWidget(ui.announcementPage);
}

void canteen_manager::on_canteenSearchEdit_textChanged(const QString &text)
{
    updateCanteenSearch(text);
}

void canteen_manager::on_dishSearchEdit_textChanged(const QString &text)
{
    updateDishSearch(text);
}

void canteen_manager::updateCanteenSearch(const QString &searchText)
{
    if (!canteenModel) {
        canteenModel = new QSqlQueryModel(this);
    }

    QSqlQuery query;
    if (searchText.isEmpty()) {
        query.prepare("SELECT * FROM canteens_view");
    } else {
        query.prepare("SELECT * FROM canteens_view WHERE canteen_name LIKE ? OR location LIKE ?");
        query.addBindValue("%" + searchText + "%");
        query.addBindValue("%" + searchText + "%");
    }
    
    if (!query.exec()) {
        qDebug() << "食堂搜索查询失败：" << query.lastError().text();
        return;
    }

    canteenModel->setQuery(std::move(query));
    
    // 重新设置表头
    canteenModel->setHeaderData(0, Qt::Horizontal, "食堂ID");
    canteenModel->setHeaderData(1, Qt::Horizontal, "食堂名称");
    canteenModel->setHeaderData(2, Qt::Horizontal, "简介");
    canteenModel->setHeaderData(3, Qt::Horizontal, "位置");
    canteenModel->setHeaderData(4, Qt::Horizontal, "营业时间");
    canteenModel->setHeaderData(5, Qt::Horizontal, "状态");
    canteenModel->setHeaderData(6, Qt::Horizontal, "评分");
}

void canteen_manager::updateDishSearch(const QString &searchText)
{
    if (!dishModel) {
        dishModel = new QSqlQueryModel(this);
    }

    QSqlQuery query;
    if (searchText.isEmpty()) {
        query.prepare("SELECT d.*, c.canteen_name FROM dishes d "
                     "LEFT JOIN canteens c ON d.canteen_id = c.canteen_id");
    } else {
        query.prepare("SELECT d.*, c.canteen_name FROM dishes d "
                     "LEFT JOIN canteens c ON d.canteen_id = c.canteen_id "
                     "WHERE d.dish_name LIKE ? OR c.canteen_name LIKE ?");
        query.addBindValue("%" + searchText + "%");
        query.addBindValue("%" + searchText + "%");
    }
    
    if (!query.exec()) {
        qDebug() << "菜品搜索查询失败：" << query.lastError().text();
        return;
    }

    dishModel->setQuery(std::move(query));
    
    // 重新设置表头
    dishModel->setHeaderData(0, Qt::Horizontal, "菜品ID");
    dishModel->setHeaderData(1, Qt::Horizontal, "食堂ID");
    dishModel->setHeaderData(2, Qt::Horizontal, "菜品名称");
    dishModel->setHeaderData(3, Qt::Horizontal, "描述");
    dishModel->setHeaderData(4, Qt::Horizontal, "价格");
    dishModel->setHeaderData(5, Qt::Horizontal, "类别");
    dishModel->setHeaderData(6, Qt::Horizontal, "是否可用");
    dishModel->setHeaderData(7, Qt::Horizontal, "图片路径");
    dishModel->setHeaderData(8, Qt::Horizontal, "销量");
    dishModel->setHeaderData(9, Qt::Horizontal, "评分");
    dishModel->setHeaderData(12, Qt::Horizontal, "所属食堂");

    // 隐藏不需要显示的列
    ui.dishManageTableView->hideColumn(7);  // 图片路径
    ui.dishManageTableView->hideColumn(10); // created_at
    ui.dishManageTableView->hideColumn(11); // updated_at
}

void canteen_manager::showCanteenManagePage()
{
    // 初始化模型
    if (!canteenModel) {
        canteenModel = new QSqlQueryModel(this);
    }

    // 使用视图获取食堂信息
    canteenModel->setQuery("SELECT * FROM canteens_view");
    
    if (canteenModel->lastError().isValid()) {
        QMessageBox::critical(this, "错误", "获取食堂信息失败：" + canteenModel->lastError().text());
        return;
    }

    // 设置表头
    canteenModel->setHeaderData(0, Qt::Horizontal, "食堂ID");
    canteenModel->setHeaderData(1, Qt::Horizontal, "食堂名称");
    canteenModel->setHeaderData(2, Qt::Horizontal, "简介");
    canteenModel->setHeaderData(3, Qt::Horizontal, "位置");
    canteenModel->setHeaderData(4, Qt::Horizontal, "营业时间");
    canteenModel->setHeaderData(5, Qt::Horizontal, "状态");
    canteenModel->setHeaderData(6, Qt::Horizontal, "评分");

    // 设置表格视图
    ui.canteenManageTableView->setModel(canteenModel);
    
    // 设置表格样式
    ui.canteenManageTableView->setStyleSheet(
        "QTableView {"
        "   background-color: white;"
        "   alternate-background-color: #f6f6f6;"
        "   selection-background-color: #0078d7;"
        "   selection-color: white;"
        "   border: 1px solid #c0c0c0;"
        "   gridline-color: #e0e0e0;"
        "}"
        "QHeaderView::section {"
        "   background-color: #f0f0f0;"
        "   color: black;"
        "   padding: 4px;"
        "   border: 1px solid #c0c0c0;"
        "   font-weight: bold;"
        "}"
    );

    // 设置表格属性
    ui.canteenManageTableView->setAlternatingRowColors(true);
    ui.canteenManageTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui.canteenManageTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui.canteenManageTableView->verticalHeader()->setDefaultSectionSize(30);
    ui.canteenManageTableView->verticalHeader()->setVisible(false);
    ui.canteenManageTableView->horizontalHeader()->setStretchLastSection(true);

    // 设置列宽
    ui.canteenManageTableView->setColumnWidth(0, 60);   // ID列
    ui.canteenManageTableView->setColumnWidth(1, 100);  // 食堂名称
    ui.canteenManageTableView->setColumnWidth(2, 200);  // 简介
    ui.canteenManageTableView->setColumnWidth(3, 150);  // 位置
    ui.canteenManageTableView->setColumnWidth(4, 100);  // 营业时间
    ui.canteenManageTableView->setColumnWidth(5, 80);   // 状态
    ui.canteenManageTableView->setColumnWidth(6, 60);   // 评分

    // 清空搜索框
    ui.canteenManageSearchEdit->clear();

    // 切换到食堂管理页面
    ui.contentStackedWidget->setCurrentWidget(ui.canteenManagePage);
}

// 添加食堂
void canteen_manager::on_addCanteenButton_clicked()
{
    // TODO: 实现添加食堂功能
    QDialog dialog(this);
    dialog.setWindowTitle("添加食堂");
    dialog.setMinimumWidth(400);

    // 创建表单布局
    QFormLayout form(&dialog);

    // 创建输入控件
    QLineEdit nameEdit;
    QTextEdit descEdit;
    QLineEdit locationEdit;
    QLineEdit hoursEdit;
    QComboBox statusCombo;

    // 设置状态选项
    statusCombo.addItem("营业中", "open");
    statusCombo.addItem("已关闭", "closed");
    statusCombo.addItem("装修中", "renovating");

    // 添加表单项
    form.addRow("食堂名称:", &nameEdit);
    form.addRow("简介:", &descEdit);
    form.addRow("位置:", &locationEdit);
    form.addRow("营业时间:", &hoursEdit);
    form.addRow("状态:", &statusCombo);

    // 添加确定和取消按钮
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                             Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);

    // 连接按钮信号
    connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    // 显示对话框
    if (dialog.exec() == QDialog::Accepted) {
        // 获取输入的值
        QString name = nameEdit.text().trimmed();
        QString desc = descEdit.toPlainText().trimmed();
        QString location = locationEdit.text().trimmed();
        QString hours = hoursEdit.text().trimmed();
        QString status = statusCombo.currentData().toString();

        // 验证输入
        if (name.isEmpty() || location.isEmpty() || hours.isEmpty()) {
            QMessageBox::warning(this, "警告", "食堂名称、位置和营业时间不能为空！");
            return;
        }

        // 执行插入操作
        QSqlQuery query;
        query.prepare("INSERT INTO canteens (canteen_name, description, location, opening_hours, status) "
                     "VALUES (?, ?, ?, ?, ?)");
        query.addBindValue(name);
        query.addBindValue(desc);
        query.addBindValue(location);
        query.addBindValue(hours);
        query.addBindValue(status);

        if (query.exec()) {
            QMessageBox::information(this, "成功", "食堂添加成功！");
            // 刷新表格
            showCanteenManagePage();
        } else {
            QMessageBox::critical(this, "错误", "添加食堂失败：" + query.lastError().text());
        }
    }
}

// 编辑食堂
void canteen_manager::on_editCanteenButton_clicked()
{
    // 获取选中的行
    QModelIndex currentIndex = ui.canteenManageTableView->currentIndex();
    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "警告", "请先选择要编辑的食堂！");
        return;
    }

    // 获取食堂ID和当前信息
    int row = currentIndex.row();
    int canteenId = canteenModel->data(canteenModel->index(row, 0)).toInt();
    QString currentName = canteenModel->data(canteenModel->index(row, 1)).toString();
    QString currentDesc = canteenModel->data(canteenModel->index(row, 2)).toString();
    QString currentLocation = canteenModel->data(canteenModel->index(row, 3)).toString();
    QString currentHours = canteenModel->data(canteenModel->index(row, 4)).toString();
    QString currentStatus = canteenModel->data(canteenModel->index(row, 5)).toString();

    // 创建编辑对话框
    QDialog dialog(this);
    dialog.setWindowTitle("编辑食堂");
    dialog.setMinimumWidth(400);

    // 创建表单布局
    QFormLayout form(&dialog);

    // 创建输入控件
    QLineEdit nameEdit(currentName);
    QTextEdit descEdit;
    descEdit.setText(currentDesc);
    QLineEdit locationEdit(currentLocation);
    QLineEdit hoursEdit(currentHours);
    QComboBox statusCombo;

    // 设置状态选项
    statusCombo.addItem("营业中", "open");
    statusCombo.addItem("已关闭", "closed");
    statusCombo.addItem("装修中", "renovating");
    
    // 设置当前状态
    int statusIndex = statusCombo.findData(currentStatus);
    if (statusIndex != -1) {
        statusCombo.setCurrentIndex(statusIndex);
    }

    // 添加表单项
    form.addRow("食堂名称:", &nameEdit);
    form.addRow("简介:", &descEdit);
    form.addRow("位置:", &locationEdit);
    form.addRow("营业时间:", &hoursEdit);
    form.addRow("状态:", &statusCombo);

    // 添加确定和取消按钮
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                             Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);

    // 连接按钮信号
    connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    // 显示对话框
    if (dialog.exec() == QDialog::Accepted) {
        // 获取修改后的值
        QString name = nameEdit.text().trimmed();
        QString desc = descEdit.toPlainText().trimmed();
        QString location = locationEdit.text().trimmed();
        QString hours = hoursEdit.text().trimmed();
        QString status = statusCombo.currentData().toString();

        // 验证输入
        if (name.isEmpty() || location.isEmpty() || hours.isEmpty()) {
            QMessageBox::warning(this, "警告", "食堂名称、位置和营业时间不能为空！");
            return;
        }

        // 执行更新操作
        QSqlQuery query;
        query.prepare("UPDATE canteens SET canteen_name = ?, description = ?, "
                     "location = ?, opening_hours = ?, status = ? "
                     "WHERE canteen_id = ?");
        query.addBindValue(name);
        query.addBindValue(desc);
        query.addBindValue(location);
        query.addBindValue(hours);
        query.addBindValue(status);
        query.addBindValue(canteenId);

        if (query.exec()) {
            QMessageBox::information(this, "成功", "食堂信息更新成功！");
            // 刷新表格
            showCanteenManagePage();
        } else {
            QMessageBox::critical(this, "错误", "更新食堂信息失败：" + query.lastError().text());
        }
    }
}

// 删除食堂
void canteen_manager::on_deleteCanteenButton_clicked()
{
    // 获取选中的行
    QModelIndex currentIndex = ui.canteenManageTableView->currentIndex();
    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "警告", "请先选择要删除的食堂！");
        return;
    }

    // 获取食堂信息
    int row = currentIndex.row();
    int canteenId = canteenModel->data(canteenModel->index(row, 0)).toInt();
    QString canteenName = canteenModel->data(canteenModel->index(row, 1)).toString();

    // 确认删除
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认删除",
        QString("确定要删除食堂\"%1\"吗？\n删除后将无法恢复！").arg(canteenName),
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // 检查是否有关联的菜品
        QSqlQuery checkQuery;
        checkQuery.prepare("SELECT COUNT(*) FROM dishes WHERE canteen_id = ?");
        checkQuery.addBindValue(canteenId);
        
        if (checkQuery.exec() && checkQuery.next()) {
            int dishCount = checkQuery.value(0).toInt();
            if (dishCount > 0) {
                QMessageBox::warning(this, "警告", 
                    QString("无法删除食堂\"%1\"，因为还有%2个关联的菜品。\n请先删除或转移这些菜品。")
                    .arg(canteenName)
                    .arg(dishCount));
                return;
            }
        }

        // 执行删除操作
        QSqlQuery query;
        query.prepare("DELETE FROM canteens WHERE canteen_id = ?");
        query.addBindValue(canteenId);

        if (query.exec()) {
            QMessageBox::information(this, "成功", "食堂删除成功！");
            // 刷新表格
            showCanteenManagePage();
        } else {
            QMessageBox::critical(this, "错误", "删除食堂失败：" + query.lastError().text());
        }
    }
}

void canteen_manager::showDishManagePage()
{
    // 初始化模型
    if (!dishModel) {
        dishModel = new QSqlQueryModel(this);
    }

    // 使用视图获取菜品信息
    dishModel->setQuery("SELECT d.*, c.canteen_name FROM dishes d "
                       "LEFT JOIN canteens c ON d.canteen_id = c.canteen_id");
    
    if (dishModel->lastError().isValid()) {
        QMessageBox::critical(this, "错误", "获取菜品信息失败：" + dishModel->lastError().text());
        return;
    }

    // 设置表头
    dishModel->setHeaderData(0, Qt::Horizontal, "菜品ID");
    dishModel->setHeaderData(1, Qt::Horizontal, "食堂ID");
    dishModel->setHeaderData(2, Qt::Horizontal, "菜品名称");
    dishModel->setHeaderData(3, Qt::Horizontal, "描述");
    dishModel->setHeaderData(4, Qt::Horizontal, "价格");
    dishModel->setHeaderData(5, Qt::Horizontal, "类别");
    dishModel->setHeaderData(6, Qt::Horizontal, "是否可用");
    dishModel->setHeaderData(7, Qt::Horizontal, "图片路径");
    dishModel->setHeaderData(8, Qt::Horizontal, "销量");
    dishModel->setHeaderData(9, Qt::Horizontal, "评分");
    dishModel->setHeaderData(12, Qt::Horizontal, "所属食堂");

    // 设置表格视图
    ui.dishManageTableView->setModel(dishModel);
    
    // 设置表格样式
    ui.dishManageTableView->setStyleSheet(
        "QTableView {"
        "   background-color: white;"
        "   alternate-background-color: #f6f6f6;"
        "   selection-background-color: #0078d7;"
        "   selection-color: white;"
        "   border: 1px solid #c0c0c0;"
        "   gridline-color: #e0e0e0;"
        "}"
        "QHeaderView::section {"
        "   background-color: #f0f0f0;"
        "   color: black;"
        "   padding: 4px;"
        "   border: 1px solid #c0c0c0;"
        "   font-weight: bold;"
        "}"
    );

    // 设置表格属性
    ui.dishManageTableView->setAlternatingRowColors(true);
    ui.dishManageTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui.dishManageTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui.dishManageTableView->verticalHeader()->setDefaultSectionSize(30);
    ui.dishManageTableView->verticalHeader()->setVisible(false);
    ui.dishManageTableView->horizontalHeader()->setStretchLastSection(true);

    // 设置列宽
    ui.dishManageTableView->setColumnWidth(0, 60);   // ID列
    ui.dishManageTableView->setColumnWidth(1, 60);   // 食堂ID
    ui.dishManageTableView->setColumnWidth(2, 120);  // 菜品名称
    ui.dishManageTableView->setColumnWidth(3, 200);  // 描述
    ui.dishManageTableView->setColumnWidth(4, 80);   // 价格
    ui.dishManageTableView->setColumnWidth(5, 80);   // 类别
    ui.dishManageTableView->setColumnWidth(6, 80);   // 是否可用
    ui.dishManageTableView->setColumnWidth(8, 60);   // 销量
    ui.dishManageTableView->setColumnWidth(9, 60);   // 评分
    ui.dishManageTableView->setColumnWidth(12, 100); // 所属食堂

    // 隐藏不需要显示的列
    ui.dishManageTableView->hideColumn(7);  // 图片路径
    ui.dishManageTableView->hideColumn(10); // created_at
    ui.dishManageTableView->hideColumn(11); // updated_at

    // 清空搜索框
    ui.dishManageSearchEdit->clear();

    // 清空图片显示
    ui.dishManageImageLabel->setPixmap(defaultDishImage);
    ui.dishManageNameLabel->clear();
    ui.dishManagePriceLabel->clear();

    // 切换到菜品管理页面
    ui.contentStackedWidget->setCurrentWidget(ui.dishManagePage);
}

void canteen_manager::on_dishManageTableView_clicked(const QModelIndex &index)
{
    if (!index.isValid()) return;

    // 获取选中行的数据
    int row = index.row();
    QString dishName = dishModel->data(dishModel->index(row, 2)).toString();
    QString price = QString("￥%1").arg(dishModel->data(dishModel->index(row, 4)).toString());
    QString imagePath = dishModel->data(dishModel->index(row, 7)).toString();

    // 更新菜品名称和价格
    ui.dishManageNameLabel->setText(dishName);
    ui.dishManagePriceLabel->setText(price);

    // 加载图片
    QPixmap image(imagePath);
    if (image.isNull()) {
        ui.dishManageImageLabel->setPixmap(defaultDishImage);
    } else {
        ui.dishManageImageLabel->setPixmap(image.scaled(280, 280, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

QString canteen_manager::selectImageFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        "选择图片",
        "",
        "图片文件 (*.png *.jpg *.jpeg *.bmp)");
    
    return fileName;
}

QString canteen_manager::saveImageToResources(const QString &sourcePath)
{
    if (sourcePath.isEmpty()) {
        return QString();
    }

    // 创建资源目录（如果不存在）
    QDir resourceDir("resources/images/dishes");
    if (!resourceDir.exists()) {
        resourceDir.mkpath(".");
    }

    // 生成唯一的文件名
    QFileInfo sourceFile(sourcePath);
    QString fileName = QDateTime::currentDateTime().toString("yyyyMMddhhmmss_") + 
                      sourceFile.fileName();
    QString destPath = resourceDir.filePath(fileName);

    // 复制文件
    if (QFile::copy(sourcePath, destPath)) {
        return destPath;
    }

    return QString();
}

void canteen_manager::on_addDishButton_clicked()
{
    // 创建对话框
    QDialog dialog(this);
    dialog.setWindowTitle("添加菜品");
    dialog.setMinimumWidth(500);

    // 创建表单布局
    QFormLayout form(&dialog);

    // 创建输入控件
    QLineEdit nameEdit;
    QTextEdit descEdit;
    QLineEdit priceEdit;
    QLineEdit categoryEdit;
    QComboBox statusCombo;
    QComboBox canteenCombo;

    // 创建图片选择相关控件
    QHBoxLayout* imageLayout = new QHBoxLayout;
    QLabel* imageLabel = new QLabel;
    imageLabel->setMinimumSize(100, 100);
    imageLabel->setMaximumSize(100, 100);
    imageLabel->setScaledContents(true);
    imageLabel->setStyleSheet("border: 1px solid #cccccc; background-color: white;");
    QPushButton* selectImageButton = new QPushButton("选择图片");
    imageLayout->addWidget(imageLabel);
    imageLayout->addWidget(selectImageButton);
    imageLayout->addStretch();

    // 设置状态选项
    statusCombo.addItem("可用", true);
    statusCombo.addItem("不可用", false);

    // 获取食堂列表
    QSqlQuery canteenQuery("SELECT canteen_id, canteen_name FROM canteens");
    while (canteenQuery.next()) {
        canteenCombo.addItem(canteenQuery.value(1).toString(), canteenQuery.value(0));
    }

    // 添加表单项
    form.addRow("菜品名称:", &nameEdit);
    form.addRow("所属食堂:", &canteenCombo);
    form.addRow("描述:", &descEdit);
    form.addRow("价格:", &priceEdit);
    form.addRow("类别:", &categoryEdit);
    form.addRow("状态:", &statusCombo);
    form.addRow("图片:", imageLayout);

    // 添加确定和取消按钮
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                             Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);

    // 连接图片选择按钮信号
    currentImagePath.clear();
    connect(selectImageButton, &QPushButton::clicked, [this, imageLabel]() {
        QString fileName = selectImageFile();
        if (!fileName.isEmpty()) {
            currentImagePath = fileName;
            QPixmap pixmap(fileName);
            imageLabel->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    });

    // 连接按钮信号
    connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    // 显示对话框
    if (dialog.exec() == QDialog::Accepted) {
        // 获取输入的值
        QString name = nameEdit.text().trimmed();
        int canteenId = canteenCombo.currentData().toInt();
        QString desc = descEdit.toPlainText().trimmed();
        QString price = priceEdit.text().trimmed();
        QString category = categoryEdit.text().trimmed();
        bool isAvailable = statusCombo.currentData().toBool();

        // 验证输入
        if (name.isEmpty() || price.isEmpty() || category.isEmpty()) {
            QMessageBox::warning(this, "警告", "菜品名称、价格和类别不能为空！");
            return;
        }

        // 验证价格格式
        bool ok;
        double priceValue = price.toDouble(&ok);
        if (!ok || priceValue <= 0) {
            QMessageBox::warning(this, "警告", "请输入有效的价格！");
            return;
        }

        // 保存图片到资源目录
        QString savedImagePath;
        if (!currentImagePath.isEmpty()) {
            savedImagePath = saveImageToResources(currentImagePath);
            if (savedImagePath.isEmpty()) {
                QMessageBox::warning(this, "警告", "图片保存失败！");
                return;
            }
        }

        // 执行插入操作
        QSqlQuery query;
        query.prepare("INSERT INTO dishes (canteen_id, dish_name, description, price, category, is_available, image_path) "
                     "VALUES (?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue(canteenId);
        query.addBindValue(name);
        query.addBindValue(desc);
        query.addBindValue(priceValue);
        query.addBindValue(category);
        query.addBindValue(isAvailable);
        query.addBindValue(savedImagePath);

        if (query.exec()) {
            QMessageBox::information(this, "成功", "菜品添加成功！");
            // 刷新表格
            showDishManagePage();
        } else {
            QMessageBox::critical(this, "错误", "添加菜品失败：" + query.lastError().text());
        }
    }
}

void canteen_manager::on_editDishButton_clicked()
{
    // 获取选中的行
    QModelIndex currentIndex = ui.dishManageTableView->currentIndex();
    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "警告", "请先选择要编辑的菜品！");
        return;
    }

    // 获取菜品信息
    int row = currentIndex.row();
    int dishId = dishModel->data(dishModel->index(row, 0)).toInt();
    int currentCanteenId = dishModel->data(dishModel->index(row, 1)).toInt();
    QString currentName = dishModel->data(dishModel->index(row, 2)).toString();
    QString currentDesc = dishModel->data(dishModel->index(row, 3)).toString();
    double currentPrice = dishModel->data(dishModel->index(row, 4)).toDouble();
    QString currentCategory = dishModel->data(dishModel->index(row, 5)).toString();
    bool currentStatus = dishModel->data(dishModel->index(row, 6)).toBool();
    QString currentImagePath = dishModel->data(dishModel->index(row, 7)).toString();

    // 创建对话框
    QDialog dialog(this);
    dialog.setWindowTitle("编辑菜品");
    dialog.setMinimumWidth(500);

    // 创建表单布局
    QFormLayout form(&dialog);

    // 创建输入控件
    QLineEdit nameEdit(currentName);
    QTextEdit descEdit;
    descEdit.setText(currentDesc);
    QLineEdit priceEdit(QString::number(currentPrice, 'f', 2));
    QLineEdit categoryEdit(currentCategory);
    QComboBox statusCombo;
    QComboBox canteenCombo;

    // 创建图片选择相关控件
    QHBoxLayout* imageLayout = new QHBoxLayout;
    QLabel* imageLabel = new QLabel;
    imageLabel->setMinimumSize(100, 100);
    imageLabel->setMaximumSize(100, 100);
    imageLabel->setScaledContents(true);
    imageLabel->setStyleSheet("border: 1px solid #cccccc; background-color: white;");
    
    // 显示当前图片
    if (!currentImagePath.isEmpty()) {
        QPixmap pixmap(currentImagePath);
        if (!pixmap.isNull()) {
            imageLabel->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    }
    
    QPushButton* selectImageButton = new QPushButton("选择图片");
    imageLayout->addWidget(imageLabel);
    imageLayout->addWidget(selectImageButton);
    imageLayout->addStretch();

    // 设置状态选项
    statusCombo.addItem("可用", true);
    statusCombo.addItem("不可用", false);
    statusCombo.setCurrentIndex(currentStatus ? 0 : 1);

    // 获取食堂列表
    QSqlQuery canteenQuery("SELECT canteen_id, canteen_name FROM canteens");
    int currentCanteenIndex = 0;
    int index = 0;
    while (canteenQuery.next()) {
        int canteenId = canteenQuery.value(0).toInt();
        QString canteenName = canteenQuery.value(1).toString();
        canteenCombo.addItem(canteenName, canteenId);
        if (canteenId == currentCanteenId) {
            currentCanteenIndex = index;
        }
        index++;
    }
    canteenCombo.setCurrentIndex(currentCanteenIndex);

    // 添加表单项
    form.addRow("菜品名称:", &nameEdit);
    form.addRow("所属食堂:", &canteenCombo);
    form.addRow("描述:", &descEdit);
    form.addRow("价格:", &priceEdit);
    form.addRow("类别:", &categoryEdit);
    form.addRow("状态:", &statusCombo);
    form.addRow("图片:", imageLayout);

    // 添加确定和取消按钮
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                             Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);

    // 连接图片选择按钮信号
    this->currentImagePath = currentImagePath;
    connect(selectImageButton, &QPushButton::clicked, [this, imageLabel]() {
        QString fileName = selectImageFile();
        if (!fileName.isEmpty()) {
            this->currentImagePath = fileName;
            QPixmap pixmap(fileName);
            imageLabel->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    });

    // 连接按钮信号
    connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    // 显示对话框
    if (dialog.exec() == QDialog::Accepted) {
        // 获取修改后的值
        QString name = nameEdit.text().trimmed();
        int canteenId = canteenCombo.currentData().toInt();
        QString desc = descEdit.toPlainText().trimmed();
        QString price = priceEdit.text().trimmed();
        QString category = categoryEdit.text().trimmed();
        bool isAvailable = statusCombo.currentData().toBool();

        // 验证输入
        if (name.isEmpty() || price.isEmpty() || category.isEmpty()) {
            QMessageBox::warning(this, "警告", "菜品名称、价格和类别不能为空！");
            return;
        }

        // 验证价格格式
        bool ok;
        double priceValue = price.toDouble(&ok);
        if (!ok || priceValue <= 0) {
            QMessageBox::warning(this, "警告", "请输入有效的价格！");
            return;
        }

        // 如果选择了新图片，保存到资源目录
        QString savedImagePath = this->currentImagePath;
        if (this->currentImagePath != currentImagePath) {
            savedImagePath = saveImageToResources(this->currentImagePath);
            if (savedImagePath.isEmpty()) {
                QMessageBox::warning(this, "警告", "图片保存失败！");
                return;
            }
        }

        // 执行更新操作
        QSqlQuery query;
        query.prepare("UPDATE dishes SET canteen_id = ?, dish_name = ?, description = ?, "
                     "price = ?, category = ?, is_available = ?, image_path = ? "
                     "WHERE dish_id = ?");
        query.addBindValue(canteenId);
        query.addBindValue(name);
        query.addBindValue(desc);
        query.addBindValue(priceValue);
        query.addBindValue(category);
        query.addBindValue(isAvailable);
        query.addBindValue(savedImagePath);
        query.addBindValue(dishId);

        if (query.exec()) {
            QMessageBox::information(this, "成功", "菜品信息更新成功！");
            // 刷新表格
            showDishManagePage();
        } else {
            QMessageBox::critical(this, "错误", "更新菜品信息失败：" + query.lastError().text());
        }
    }
}

void canteen_manager::on_deleteDishButton_clicked()
{
    // 获取选中的行
    QModelIndex currentIndex = ui.dishManageTableView->currentIndex();
    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "警告", "请先选择要删除的菜品！");
        return;
    }

    // 获取菜品信息
    int row = currentIndex.row();
    int dishId = dishModel->data(dishModel->index(row, 0)).toInt();
    QString dishName = dishModel->data(dishModel->index(row, 2)).toString();

    // 确认删除
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认删除",
        QString("确定要删除菜品\"%1\"吗？\n删除后将无法恢复！").arg(dishName),
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // 执行删除操作
        QSqlQuery query;
        query.prepare("DELETE FROM dishes WHERE dish_id = ?");
        query.addBindValue(dishId);

        if (query.exec()) {
            QMessageBox::information(this, "成功", "菜品删除成功！");
            // 刷新表格
            showDishManagePage();
        } else {
            QMessageBox::critical(this, "错误", "删除菜品失败：" + query.lastError().text());
        }
    }
}

void canteen_manager::showAnnouncementManagePage()
{
    // 初始化模型
    if (!announcementModel) {
        announcementModel = new QSqlQueryModel(this);
    }

    // 查询原始公告表数据（包含所有字段）
    announcementModel->setQuery(
        "SELECT a.announcement_id, a.title, a.content, "
        "u.username as publisher_name, "
        "a.publish_date, a.is_active, "
        "a.created_at, a.updated_at "
        "FROM announcements a "
        "LEFT JOIN users u ON a.publisher_id = u.user_id "
        "ORDER BY a.publish_date DESC"
    );
    
    if (announcementModel->lastError().isValid()) {
        QMessageBox::critical(this, "错误", "获取公告信息失败：" + announcementModel->lastError().text());
        return;
    }

    // 设置表头
    announcementModel->setHeaderData(0, Qt::Horizontal, "公告ID");
    announcementModel->setHeaderData(1, Qt::Horizontal, "标题");
    announcementModel->setHeaderData(2, Qt::Horizontal, "内容");
    announcementModel->setHeaderData(3, Qt::Horizontal, "发布者");
    announcementModel->setHeaderData(4, Qt::Horizontal, "发布时间");
    announcementModel->setHeaderData(5, Qt::Horizontal, "状态");
    announcementModel->setHeaderData(6, Qt::Horizontal, "创建时间");
    announcementModel->setHeaderData(7, Qt::Horizontal, "更新时间");

    // 设置表格视图
    ui.announcementManageTableView->setModel(announcementModel);
    
    // 设置表格样式
    ui.announcementManageTableView->setStyleSheet(
        "QTableView {"
        "   background-color: white;"
        "   alternate-background-color: #f6f6f6;"
        "   selection-background-color: #0078d7;"
        "   selection-color: white;"
        "   border: 1px solid #c0c0c0;"
        "   gridline-color: #e0e0e0;"
        "}"
        "QHeaderView::section {"
        "   background-color: #f0f0f0;"
        "   color: black;"
        "   padding: 4px;"
        "   border: 1px solid #c0c0c0;"
        "   font-weight: bold;"
        "}"
    );

    // 设置表格属性
    ui.announcementManageTableView->setAlternatingRowColors(true);
    ui.announcementManageTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui.announcementManageTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui.announcementManageTableView->verticalHeader()->setDefaultSectionSize(30);
    ui.announcementManageTableView->verticalHeader()->setVisible(false);
    ui.announcementManageTableView->horizontalHeader()->setStretchLastSection(true);

    // 设置列宽
    ui.announcementManageTableView->setColumnWidth(0, 60);   // ID列
    ui.announcementManageTableView->setColumnWidth(1, 150);  // 标题
    ui.announcementManageTableView->setColumnWidth(2, 250);  // 内容
    ui.announcementManageTableView->setColumnWidth(3, 100);  // 发布者
    ui.announcementManageTableView->setColumnWidth(4, 150);  // 发布时间
    ui.announcementManageTableView->setColumnWidth(5, 80);   // 状态
    ui.announcementManageTableView->setColumnWidth(6, 150);  // 创建时间
    ui.announcementManageTableView->setColumnWidth(7, 150);  // 更新时间

    // 清空搜索框
    ui.announcementManageSearchEdit->clear();

    // 切换到公告管理页面
    ui.contentStackedWidget->setCurrentWidget(ui.announcementManagePage);
}

void canteen_manager::on_addAnnouncementButton_clicked()
{
    // 创建对话框
    QDialog dialog(this);
    dialog.setWindowTitle("添加公告");
    dialog.setMinimumWidth(500);

    // 创建表单布局
    QFormLayout form(&dialog);

    // 创建输入控件
    QLineEdit titleEdit;
    QTextEdit contentEdit;
    QComboBox statusCombo;

    // 设置文本框的最小高度
    contentEdit.setMinimumHeight(200);

    // 设置状态选项
    statusCombo.addItem("已发布", true);
    statusCombo.addItem("未发布", false);

    // 添加表单项
    form.addRow("标题:", &titleEdit);
    form.addRow("内容:", &contentEdit);
    form.addRow("状态:", &statusCombo);

    // 添加确定和取消按钮
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                             Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);

    // 连接按钮信号
    connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    // 显示对话框
    if (dialog.exec() == QDialog::Accepted) {
        // 获取输入的值
        QString title = titleEdit.text().trimmed();
        QString content = contentEdit.toPlainText().trimmed();
        bool isActive = statusCombo.currentData().toBool();

        // 验证输入
        if (title.isEmpty() || content.isEmpty()) {
            QMessageBox::warning(this, "警告", "标题和内容不能为空！");
            return;
        }

        // 执行插入操作
        QSqlQuery query;
        
        // 首先获取当前用户的ID
        QSqlQuery userQuery;
        userQuery.prepare("SELECT user_id FROM users WHERE username = ?");
        userQuery.addBindValue(currentUser);
        
        int publisherId = -1;
        if (userQuery.exec() && userQuery.next()) {
            publisherId = userQuery.value(0).toInt();
        } else {
            QMessageBox::critical(this, "错误", "获取用户信息失败！");
            return;
        }

        // 插入公告
        query.prepare("INSERT INTO announcements (title, content, publisher_id, is_active) "
                     "VALUES (?, ?, ?, ?)");
        query.addBindValue(title);
        query.addBindValue(content);
        query.addBindValue(publisherId);
        query.addBindValue(isActive);

        if (query.exec()) {
            QMessageBox::information(this, "成功", "公告添加成功！");
            // 刷新表格
            showAnnouncementManagePage();
        } else {
            QMessageBox::critical(this, "错误", "添加公告失败：" + query.lastError().text());
        }
    }
}

void canteen_manager::on_editAnnouncementButton_clicked()
{
    // 获取选中的行
    QModelIndex currentIndex = ui.announcementManageTableView->currentIndex();
    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "警告", "请先选择要编辑的公告！");
        return;
    }

    // 获取公告信息
    int row = currentIndex.row();
    int announcementId = announcementModel->data(announcementModel->index(row, 0)).toInt();
    QString currentTitle = announcementModel->data(announcementModel->index(row, 1)).toString();
    QString currentContent = announcementModel->data(announcementModel->index(row, 2)).toString();
    bool currentStatus = announcementModel->data(announcementModel->index(row, 5)).toBool();

    // 创建编辑对话框
    QDialog dialog(this);
    dialog.setWindowTitle("编辑公告");
    dialog.setMinimumWidth(500);

    // 创建表单布局
    QFormLayout form(&dialog);

    // 创建输入控件
    QLineEdit titleEdit(currentTitle);
    QTextEdit contentEdit;
    contentEdit.setText(currentContent);
    QComboBox statusCombo;

    // 设置文本框的最小高度
    contentEdit.setMinimumHeight(200);

    // 设置状态选项
    statusCombo.addItem("生效中", true);
    statusCombo.addItem("已结束", false);
    statusCombo.setCurrentIndex(currentStatus ? 0 : 1);

    // 添加表单项
    form.addRow("标题:", &titleEdit);
    form.addRow("内容:", &contentEdit);
    form.addRow("状态:", &statusCombo);

    // 添加确定和取消按钮
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                             Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);

    // 连接按钮信号
    connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    // 显示对话框
    if (dialog.exec() == QDialog::Accepted) {
        // 获取修改后的值
        QString title = titleEdit.text().trimmed();
        QString content = contentEdit.toPlainText().trimmed();
        bool isActive = statusCombo.currentData().toBool();

        // 验证输入
        if (title.isEmpty() || content.isEmpty()) {
            QMessageBox::warning(this, "警告", "标题和内容不能为空！");
            return;
        }

        // 执行更新操作
        QSqlQuery query;
        query.prepare("UPDATE announcements SET title = ?, content = ?, is_active = ? "
                     "WHERE announcement_id = ?");
        query.addBindValue(title);
        query.addBindValue(content);
        query.addBindValue(isActive);
        query.addBindValue(announcementId);

        if (query.exec()) {
            QMessageBox::information(this, "成功", "公告更新成功！");
            // 刷新表格
            showAnnouncementManagePage();
        } else {
            QMessageBox::critical(this, "错误", "更新公告失败：" + query.lastError().text());
        }
    }
}

void canteen_manager::on_deleteAnnouncementButton_clicked()
{
    // 获取选中的行
    QModelIndex currentIndex = ui.announcementManageTableView->currentIndex();
    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "警告", "请先选择要删除的公告！");
        return;
    }

    // 获取公告信息
    int row = currentIndex.row();
    int announcementId = announcementModel->data(announcementModel->index(row, 0)).toInt();
    QString title = announcementModel->data(announcementModel->index(row, 1)).toString();

    // 确认删除
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认删除",
        QString("确定要删除公告\"%1\"吗？\n删除后将无法恢复！").arg(title),
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // 执行删除操作
        QSqlQuery query;
        query.prepare("DELETE FROM announcements WHERE announcement_id = ?");
        query.addBindValue(announcementId);

        if (query.exec()) {
            QMessageBox::information(this, "成功", "公告删除成功！");
            // 刷新表格
            showAnnouncementManagePage();
        } else {
            QMessageBox::critical(this, "错误", "删除公告失败：" + query.lastError().text());
        }
    }
}

void canteen_manager::on_announcementManageSearchEdit_textChanged(const QString &text)
{
    if (!announcementModel) {
        announcementModel = new QSqlQueryModel(this);
    }

    QSqlQuery query;
    if (text.isEmpty()) {
        query.prepare(
            "SELECT a.announcement_id, a.title, a.content, "
            "u.username as publisher_name, "
            "a.publish_date, a.is_active, "
            "a.created_at, a.updated_at "
            "FROM announcements a "
            "LEFT JOIN users u ON a.publisher_id = u.user_id "
            "ORDER BY a.publish_date DESC"
        );
    } else {
        query.prepare(
            "SELECT a.announcement_id, a.title, a.content, "
            "u.username as publisher_name, "
            "a.publish_date, a.is_active, "
            "a.created_at, a.updated_at "
            "FROM announcements a "
            "LEFT JOIN users u ON a.publisher_id = u.user_id "
            "WHERE a.title LIKE ? OR a.content LIKE ? "
            "ORDER BY a.publish_date DESC"
        );
        query.addBindValue("%" + text + "%");
        query.addBindValue("%" + text + "%");
    }
    
    if (!query.exec()) {
        qDebug() << "公告搜索查询失败：" << query.lastError().text();
        return;
    }

    announcementModel->setQuery(std::move(query));
    
    // 重新设置表头
    announcementModel->setHeaderData(0, Qt::Horizontal, "公告ID");
    announcementModel->setHeaderData(1, Qt::Horizontal, "标题");
    announcementModel->setHeaderData(2, Qt::Horizontal, "内容");
    announcementModel->setHeaderData(3, Qt::Horizontal, "发布者");
    announcementModel->setHeaderData(4, Qt::Horizontal, "发布时间");
    announcementModel->setHeaderData(5, Qt::Horizontal, "状态");
    announcementModel->setHeaderData(6, Qt::Horizontal, "创建时间");
    announcementModel->setHeaderData(7, Qt::Horizontal, "更新时间");
}

void canteen_manager::showUserManagePage()
{
    // 初始化模型
    if (!userModel) {
        userModel = new QSqlQueryModel(this);
    }

    // 使用视图获取用户信息
    userModel->setQuery("SELECT * FROM users_view");
    
    if (userModel->lastError().isValid()) {
        QMessageBox::critical(this, "错误", "获取用户信息失败：" + userModel->lastError().text());
        return;
    }

    // 设置表头
    userModel->setHeaderData(0, Qt::Horizontal, "用户ID");
    userModel->setHeaderData(1, Qt::Horizontal, "用户名");
    userModel->setHeaderData(2, Qt::Horizontal, "性别");
    userModel->setHeaderData(3, Qt::Horizontal, "电话");
    userModel->setHeaderData(4, Qt::Horizontal, "邮箱");
    userModel->setHeaderData(5, Qt::Horizontal, "地址");
    userModel->setHeaderData(6, Qt::Horizontal, "用户类型");
    userModel->setHeaderData(7, Qt::Horizontal, "状态");
    userModel->setHeaderData(8, Qt::Horizontal, "最后登录");
    userModel->setHeaderData(9, Qt::Horizontal, "创建时间");
    userModel->setHeaderData(10, Qt::Horizontal, "更新时间");

    // 设置表格视图
    ui.userManageTableView->setModel(userModel);
    
    // 设置表格样式
    ui.userManageTableView->setStyleSheet(
        "QTableView {"
        "   background-color: white;"
        "   alternate-background-color: #f6f6f6;"
        "   selection-background-color: #0078d7;"
        "   selection-color: white;"
        "   border: 1px solid #c0c0c0;"
        "   gridline-color: #e0e0e0;"
        "}"
        "QHeaderView::section {"
        "   background-color: #f0f0f0;"
        "   color: black;"
        "   padding: 4px;"
        "   border: 1px solid #c0c0c0;"
        "   font-weight: bold;"
        "}"
    );

    // 设置表格属性
    ui.userManageTableView->setAlternatingRowColors(true);
    ui.userManageTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui.userManageTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui.userManageTableView->verticalHeader()->setDefaultSectionSize(30);
    ui.userManageTableView->verticalHeader()->setVisible(false);
    ui.userManageTableView->horizontalHeader()->setStretchLastSection(true);

    // 设置列宽
    ui.userManageTableView->setColumnWidth(0, 60);   // ID列
    ui.userManageTableView->setColumnWidth(1, 100);  // 用户名
    ui.userManageTableView->setColumnWidth(2, 60);   // 性别
    ui.userManageTableView->setColumnWidth(3, 100);  // 电话
    ui.userManageTableView->setColumnWidth(4, 150);  // 邮箱
    ui.userManageTableView->setColumnWidth(5, 200);  // 地址
    ui.userManageTableView->setColumnWidth(6, 80);   // 用户类型
    ui.userManageTableView->setColumnWidth(7, 80);   // 状态
    ui.userManageTableView->setColumnWidth(8, 150);  // 最后登录
    ui.userManageTableView->setColumnWidth(9, 150);  // 创建时间
    ui.userManageTableView->setColumnWidth(10, 150); // 更新时间

    // 清空搜索框
    ui.userManageSearchEdit->clear();

    // 切换到用户管理页面
    ui.contentStackedWidget->setCurrentWidget(ui.userManagePage);
}

void canteen_manager::on_addUserButton_clicked()
{
    // 创建对话框
    QDialog dialog(this);
    dialog.setWindowTitle("添加用户");
    dialog.setMinimumWidth(400);

    // 创建表单布局
    QFormLayout form(&dialog);

    // 创建输入控件
    QLineEdit usernameEdit;
    QLineEdit passwordEdit;
    QLineEdit phoneEdit;
    QLineEdit emailEdit;
    QLineEdit addressEdit;
    QComboBox genderCombo;
    QComboBox userTypeCombo;
    QComboBox statusCombo;

    // 设置密码输入框为密码模式
    passwordEdit.setEchoMode(QLineEdit::Password);

    // 设置性别选项
    genderCombo.addItem("男", "male");
    genderCombo.addItem("女", "female");
    genderCombo.addItem("其他", "other");

    // 设置用户类型选项
    userTypeCombo.addItem("普通用户", "user");
    userTypeCombo.addItem("管理员", "admin");

    // 设置状态选项
    statusCombo.addItem("激活", "active");
    statusCombo.addItem("禁用", "inactive");

    // 添加表单项
    form.addRow("用户名:", &usernameEdit);
    form.addRow("密码:", &passwordEdit);
    form.addRow("性别:", &genderCombo);
    form.addRow("电话:", &phoneEdit);
    form.addRow("邮箱:", &emailEdit);
    form.addRow("地址:", &addressEdit);
    form.addRow("用户类型:", &userTypeCombo);
    form.addRow("状态:", &statusCombo);

    // 添加确定和取消按钮
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                             Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);

    // 连接按钮信号
    connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    // 显示对话框
    if (dialog.exec() == QDialog::Accepted) {
        // 获取输入的值
        QString username = usernameEdit.text().trimmed();
        QString password = passwordEdit.text();
        QString gender = genderCombo.currentData().toString();
        QString phone = phoneEdit.text().trimmed();
        QString email = emailEdit.text().trimmed();
        QString address = addressEdit.text().trimmed();
        QString userType = userTypeCombo.currentData().toString();
        QString status = statusCombo.currentData().toString();

        // 验证输入
        if (username.isEmpty() || password.isEmpty()) {
            QMessageBox::warning(this, "警告", "用户名和密码不能为空！");
            return;
        }

        // 检查用户名是否已存在
        QSqlQuery checkQuery;
        checkQuery.prepare("SELECT COUNT(*) FROM users WHERE username = ?");
        checkQuery.addBindValue(username);
        
        if (checkQuery.exec() && checkQuery.next()) {
            if (checkQuery.value(0).toInt() > 0) {
                QMessageBox::warning(this, "警告", "用户名已存在！");
                return;
            }
        }

        // 执行插入操作
        QSqlQuery query;
        query.prepare("INSERT INTO users (username, password, gender, phone, email, address, user_type, status) "
                     "VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue(username);
        query.addBindValue(password);
        query.addBindValue(gender);
        query.addBindValue(phone);
        query.addBindValue(email);
        query.addBindValue(address);
        query.addBindValue(userType);
        query.addBindValue(status);

        if (query.exec()) {
            QMessageBox::information(this, "成功", "用户添加成功！");
            // 刷新表格
            showUserManagePage();
        } else {
            QMessageBox::critical(this, "错误", "添加用户失败：" + query.lastError().text());
        }
    }
}

void canteen_manager::on_editUserButton_clicked()
{
    // 获取选中的行
    QModelIndex currentIndex = ui.userManageTableView->currentIndex();
    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "警告", "请先选择要编辑的用户！");
        return;
    }

    // 获取用户信息
    int row = currentIndex.row();
    int userId = userModel->data(userModel->index(row, 0)).toInt();
    QString currentUsername = userModel->data(userModel->index(row, 1)).toString();
    QString currentGender = userModel->data(userModel->index(row, 2)).toString();
    QString currentPhone = userModel->data(userModel->index(row, 3)).toString();
    QString currentEmail = userModel->data(userModel->index(row, 4)).toString();
    QString currentAddress = userModel->data(userModel->index(row, 5)).toString();
    QString currentUserType = userModel->data(userModel->index(row, 6)).toString();
    QString currentStatus = userModel->data(userModel->index(row, 7)).toString();

    // 创建编辑对话框
    QDialog dialog(this);
    dialog.setWindowTitle("编辑用户");
    dialog.setMinimumWidth(400);

    // 创建表单布局
    QFormLayout form(&dialog);

    // 创建输入控件
    QLineEdit usernameEdit(currentUsername);
    QLineEdit phoneEdit(currentPhone);
    QLineEdit emailEdit(currentEmail);
    QLineEdit addressEdit(currentAddress);
    QComboBox genderCombo;
    QComboBox userTypeCombo;
    QComboBox statusCombo;

    // 设置性别选项
    genderCombo.addItem("男", "male");
    genderCombo.addItem("女", "female");
    genderCombo.addItem("其他", "other");
    genderCombo.setCurrentText(currentGender);

    // 设置用户类型选项
    userTypeCombo.addItem("普通用户", "user");
    userTypeCombo.addItem("管理员", "admin");
    userTypeCombo.setCurrentText(currentUserType);

    // 设置状态选项
    statusCombo.addItem("激活", "active");
    statusCombo.addItem("禁用", "inactive");
    statusCombo.setCurrentText(currentStatus);

    // 添加表单项
    form.addRow("用户名:", &usernameEdit);
    form.addRow("性别:", &genderCombo);
    form.addRow("电话:", &phoneEdit);
    form.addRow("邮箱:", &emailEdit);
    form.addRow("地址:", &addressEdit);
    form.addRow("用户类型:", &userTypeCombo);
    form.addRow("状态:", &statusCombo);

    // 添加确定和取消按钮
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                             Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);

    // 连接按钮信号
    connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    // 显示对话框
    if (dialog.exec() == QDialog::Accepted) {
        // 获取修改后的值
        QString username = usernameEdit.text().trimmed();
        QString gender = genderCombo.currentData().toString();
        QString phone = phoneEdit.text().trimmed();
        QString email = emailEdit.text().trimmed();
        QString address = addressEdit.text().trimmed();
        QString userType = userTypeCombo.currentData().toString();
        QString status = statusCombo.currentData().toString();

        // 验证输入
        if (username.isEmpty()) {
            QMessageBox::warning(this, "警告", "用户名不能为空！");
            return;
        }

        // 如果用户名被修改，检查是否已存在
        if (username != currentUsername) {
            QSqlQuery checkQuery;
            checkQuery.prepare("SELECT COUNT(*) FROM users WHERE username = ? AND user_id != ?");
            checkQuery.addBindValue(username);
            checkQuery.addBindValue(userId);
            
            if (checkQuery.exec() && checkQuery.next()) {
                if (checkQuery.value(0).toInt() > 0) {
                    QMessageBox::warning(this, "警告", "用户名已存在！");
                    return;
                }
            }
        }

        // 执行更新操作
        QSqlQuery query;
        query.prepare("UPDATE users SET username = ?, gender = ?, phone = ?, "
                     "email = ?, address = ?, user_type = ?, status = ? "
                     "WHERE user_id = ?");
        query.addBindValue(username);
        query.addBindValue(gender);
        query.addBindValue(phone);
        query.addBindValue(email);
        query.addBindValue(address);
        query.addBindValue(userType);
        query.addBindValue(status);
        query.addBindValue(userId);

        if (query.exec()) {
            QMessageBox::information(this, "成功", "用户信息更新成功！");
            // 刷新表格
            showUserManagePage();
        } else {
            QMessageBox::critical(this, "错误", "更新用户信息失败：" + query.lastError().text());
        }
    }
}

void canteen_manager::on_deleteUserButton_clicked()
{
    // 获取选中的行
    QModelIndex currentIndex = ui.userManageTableView->currentIndex();
    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "警告", "请先选择要删除的用户！");
        return;
    }

    // 获取用户信息
    int row = currentIndex.row();
    int userId = userModel->data(userModel->index(row, 0)).toInt();
    QString username = userModel->data(userModel->index(row, 1)).toString();

    // 不允许删除当前登录的用户
    if (username == currentUser) {
        QMessageBox::warning(this, "警告", "不能删除当前登录的用户！");
        return;
    }

    // 确认删除
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认删除",
        QString("确定要删除用户\"%1\"吗？\n删除后将无法恢复！").arg(username),
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // 执行删除操作
        QSqlQuery query;
        query.prepare("DELETE FROM users WHERE user_id = ?");
        query.addBindValue(userId);

        if (query.exec()) {
            QMessageBox::information(this, "成功", "用户删除成功！");
            // 刷新表格
            showUserManagePage();
        } else {
            QMessageBox::critical(this, "错误", "删除用户失败：" + query.lastError().text());
        }
    }
}

void canteen_manager::on_resetPasswordButton_clicked()
{
    // 获取选中的行
    QModelIndex currentIndex = ui.userManageTableView->currentIndex();
    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "警告", "请先选择要重置密码的用户！");
        return;
    }

    // 获取用户信息
    int row = currentIndex.row();
    int userId = userModel->data(userModel->index(row, 0)).toInt();
    QString username = userModel->data(userModel->index(row, 1)).toString();

    // 创建对话框
    QDialog dialog(this);
    dialog.setWindowTitle("重置密码");
    dialog.setMinimumWidth(300);

    // 创建表单布局
    QFormLayout form(&dialog);

    // 创建输入控件
    QLineEdit passwordEdit;
    QLineEdit confirmPasswordEdit;
    
    // 设置密码输入框为密码模式
    passwordEdit.setEchoMode(QLineEdit::Password);
    confirmPasswordEdit.setEchoMode(QLineEdit::Password);

    // 添加表单项
    form.addRow("新密码:", &passwordEdit);
    form.addRow("确认密码:", &confirmPasswordEdit);

    // 添加确定和取消按钮
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                             Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);

    // 连接按钮信号
    connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    // 显示对话框
    if (dialog.exec() == QDialog::Accepted) {
        // 获取输入的值
        QString password = passwordEdit.text();
        QString confirmPassword = confirmPasswordEdit.text();

        // 验证输入
        if (password.isEmpty()) {
            QMessageBox::warning(this, "警告", "密码不能为空！");
            return;
        }

        if (password != confirmPassword) {
            QMessageBox::warning(this, "警告", "两次输入的密码不一致！");
            return;
        }

        // 执行更新操作
        QSqlQuery query;
        query.prepare("UPDATE users SET password = ? WHERE user_id = ?");
        query.addBindValue(password);
        query.addBindValue(userId);

        if (query.exec()) {
            QMessageBox::information(this, "成功", QString("用户\"%1\"的密码已重置！").arg(username));
        } else {
            QMessageBox::critical(this, "错误", "重置密码失败：" + query.lastError().text());
        }
    }
}

void canteen_manager::on_userManageSearchEdit_textChanged(const QString &text)
{
    if (!userModel) {
        userModel = new QSqlQueryModel(this);
    }

    QSqlQuery query;
    if (text.isEmpty()) {
        query.prepare("SELECT * FROM users_view");
    } else {
        query.prepare("SELECT * FROM users_view WHERE "
                     "username LIKE ? OR "
                     "phone LIKE ? OR "
                     "email LIKE ?");
        QString searchPattern = "%" + text + "%";
        query.addBindValue(searchPattern);
        query.addBindValue(searchPattern);
        query.addBindValue(searchPattern);
    }
    
    if (!query.exec()) {
        qDebug() << "用户搜索查询失败：" << query.lastError().text();
        return;
    }

    userModel->setQuery(std::move(query));
    
    // 重新设置表头
    userModel->setHeaderData(0, Qt::Horizontal, "用户ID");
    userModel->setHeaderData(1, Qt::Horizontal, "用户名");
    userModel->setHeaderData(2, Qt::Horizontal, "性别");
    userModel->setHeaderData(3, Qt::Horizontal, "电话");
    userModel->setHeaderData(4, Qt::Horizontal, "邮箱");
    userModel->setHeaderData(5, Qt::Horizontal, "地址");
    userModel->setHeaderData(6, Qt::Horizontal, "用户类型");
    userModel->setHeaderData(7, Qt::Horizontal, "状态");
    userModel->setHeaderData(8, Qt::Horizontal, "最后登录");
    userModel->setHeaderData(9, Qt::Horizontal, "创建时间");
    userModel->setHeaderData(10, Qt::Horizontal, "更新时间");
}
