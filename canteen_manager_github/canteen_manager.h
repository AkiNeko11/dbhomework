#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQueryModel>
#include <QtWidgets/QTableView>
#include <QPixmap>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QDialogButtonBox>
#include "ui_canteen_manager.h"

class canteen_manager : public QMainWindow
{
    Q_OBJECT

public:
    canteen_manager(QWidget *parent = nullptr);
    ~canteen_manager();

private slots:
    // 登录相关槽函数
    void on_loginButton_clicked();    // 登录按钮点击
    void on_exitButton_clicked();     // 退出按钮点击

    // 主界面功能按钮槽函数
    void on_userManageButton_clicked();    // 用户管理
    void on_canteenManageButton_clicked(); // 食堂管理
    void on_menuManageButton_clicked();    // 菜谱管理
    void on_newsManageButton_clicked();    // 新闻公告
    void on_logoutButton_clicked();        // 退出登录
    
    // 菜单动作槽函数
    void on_actionLogout_triggered();      // 注销
    void on_actionExit_triggered();        // 退出

    // 搜索相关槽函数
    void on_canteenSearchEdit_textChanged(const QString &text);  // 食堂搜索
    void on_dishSearchEdit_textChanged(const QString &text);     // 菜品搜索

    // 表格选择相关槽函数
    void on_dishTableView_clicked(const QModelIndex &index);    // 菜品表格点击
    void on_dishManageTableView_clicked(const QModelIndex &index); // 菜品管理表格点击

    // 食堂管理相关槽函数
    void on_addCanteenButton_clicked();    // 添加食堂
    void on_editCanteenButton_clicked();   // 编辑食堂
    void on_deleteCanteenButton_clicked(); // 删除食堂

    // 菜品管理相关槽函数
    void on_addDishButton_clicked();    // 添加菜品
    void on_editDishButton_clicked();   // 编辑菜品
    void on_deleteDishButton_clicked(); // 删除菜品

    // 公告管理相关槽函数
    void on_addAnnouncementButton_clicked();    // 添加公告
    void on_editAnnouncementButton_clicked();   // 编辑公告
    void on_deleteAnnouncementButton_clicked(); // 删除公告
    void on_announcementManageSearchEdit_textChanged(const QString &text); // 搜索功能

    // 用户管理相关槽函数
    void on_addUserButton_clicked();    // 添加用户
    void on_editUserButton_clicked();   // 编辑用户
    void on_deleteUserButton_clicked(); // 删除用户
    void on_resetPasswordButton_clicked(); // 重置密码
    void on_userManageSearchEdit_textChanged(const QString &text); // 搜索功能

private:
    Ui::canteen_managerClass ui;
    
    // 数据库相关
    QSqlDatabase db;
    bool connectToDatabase();
    bool validateLogin(const QString &username, const QString &password);
    
    // 用户信息
    QString currentUser;
    QString userType;
    
    // 界面控制函数
    void setupLoginUI();      // 设置登录界面
    void setupMainUI();       // 设置主界面
    void setupAdminUI();      // 设置管理员界面
    void setupUserUI();       // 设置普通用户界面
    void switchToMainUI();    // 切换到主界面
    void switchToLoginUI();   // 切换到登录界面
    void clearLoginInfo();    // 清除登录信息

    // 普通用户查看功能
    void showCanteenInfo();       // 显示食堂信息
    void showDishInfo();          // 显示菜品信息
    void showAnnouncementInfo();  // 显示公告信息

    // 管理员功能
    void showCanteenManagePage(); // 显示食堂管理页面
    void showDishManagePage();    // 显示菜品管理页面
    void showAnnouncementManagePage(); // 显示公告管理页面

    // 用户管理相关槽函数
    void showUserManagePage();    // 显示用户管理页面

    // 表格视图相关
    QTableView* canteenTableView;     // 食堂信息表格视图
    QTableView* dishTableView;        // 菜品信息表格视图
    QTableView* announcementTableView;// 公告信息表格视图
    QSqlQueryModel* canteenModel;     // 食堂信息数据模型
    QSqlQueryModel* dishModel;        // 菜品信息数据模型
    QSqlQueryModel* announcementModel;// 公告信息数据模型
    QSqlQueryModel* userModel;        // 用户数据模型

    // 搜索功能
    void updateCanteenSearch(const QString &searchText);  // 更新食堂搜索结果
    void updateDishSearch(const QString &searchText);     // 更新菜品搜索结果

    // 图片显示功能
    void updateDishImage(const QModelIndex &index);      // 更新菜品图片
    void loadDishImage(const QString &imagePath);        // 加载菜品图片
    void clearDishImage();                              // 清除菜品图片
    QPixmap defaultDishImage;                           // 默认菜品图片
    QString currentImagePath;  // 当前选择的图片路径

    // 权限控制
    void setupUserPermissions();  // 设置用户权限


    // UI相关函数
    QString selectImageFile();  // 选择图片文件
    QString saveImageToResources(const QString &sourcePath);  // 保存图片到资源目录
};
