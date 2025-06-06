/********************************************************************************
** Form generated from reading UI file 'canteen_manager.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CANTEEN_MANAGER_H
#define UI_CANTEEN_MANAGER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_canteen_managerClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *loginPage;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QWidget *loginWidget;
    QVBoxLayout *verticalLayout_3;
    QLabel *titleLabel;
    QFormLayout *formLayout;
    QLabel *usernameLabel;
    QLineEdit *usernameEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *loginButton;
    QPushButton *exitButton;
    QLabel *Authorlabel;
    QSpacerItem *verticalSpacer_2;
    QWidget *mainPage;
    QHBoxLayout *horizontalLayout_2;
    QWidget *navWidget;
    QVBoxLayout *verticalLayout_4;
    QPushButton *userManageButton;
    QPushButton *canteenManageButton;
    QPushButton *menuManageButton;
    QPushButton *newsManageButton;
    QLabel *label_2;
    QLabel *label;
    QLabel *authorlabel;
    QSpacerItem *verticalSpacer_3;
    QPushButton *logoutButton;
    QStackedWidget *contentStackedWidget;
    QWidget *canteenPage;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_21;
    QLabel *canteenSearchLabel;
    QLineEdit *canteenSearchEdit;
    QSpacerItem *horizontalSpacer;
    QTableView *canteenTableView;
    QWidget *canteenManagePage;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *addCanteenButton;
    QPushButton *editCanteenButton;
    QPushButton *deleteCanteenButton;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *searchLayout;
    QLabel *searchLabel;
    QLineEdit *canteenManageSearchEdit;
    QSpacerItem *horizontalSpacer_4;
    QTableView *canteenManageTableView;
    QWidget *dishPage;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_3;
    QLabel *dishSearchLabel;
    QLineEdit *dishSearchEdit;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *dishContentLayout;
    QTableView *dishTableView;
    QWidget *dishImageWidget;
    QVBoxLayout *verticalLayout_8;
    QLabel *dishImageLabel;
    QLabel *dishNameLabel;
    QLabel *dishPriceLabel;
    QSpacerItem *verticalSpacer_4;
    QWidget *dishManagePage;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *addDishButton;
    QPushButton *editDishButton;
    QPushButton *deleteDishButton;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *dishSearchLayout;
    QLabel *dishManageSearchLabel;
    QLineEdit *dishManageSearchEdit;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *dishManageContentLayout;
    QTableView *dishManageTableView;
    QWidget *dishManageImageWidget;
    QVBoxLayout *verticalLayout_11;
    QLabel *dishManageImageLabel;
    QLabel *dishManageNameLabel;
    QLabel *dishManagePriceLabel;
    QSpacerItem *verticalSpacer_5;
    QWidget *announcementPage;
    QVBoxLayout *verticalLayout_7;
    QTableView *announcementTableView;
    QWidget *announcementManagePage;
    QVBoxLayout *verticalLayout_101;
    QHBoxLayout *horizontalLayout_51;
    QPushButton *addAnnouncementButton;
    QPushButton *editAnnouncementButton;
    QPushButton *deleteAnnouncementButton;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *announcementSearchLayout;
    QLabel *announcementManageSearchLabel;
    QLineEdit *announcementManageSearchEdit;
    QSpacerItem *horizontalSpacer_8;
    QTableView *announcementManageTableView;
    QWidget *userManagePage;
    QVBoxLayout *verticalLayout_12;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *addUserButton;
    QPushButton *editUserButton;
    QPushButton *deleteUserButton;
    QPushButton *resetPasswordButton;
    QSpacerItem *horizontalSpacer_9;
    QHBoxLayout *userSearchLayout;
    QLabel *userManageSearchLabel;
    QLineEdit *userManageSearchEdit;
    QSpacerItem *horizontalSpacer_10;
    QTableView *userManageTableView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *canteen_managerClass)
    {
        if (canteen_managerClass->objectName().isEmpty())
            canteen_managerClass->setObjectName("canteen_managerClass");
        canteen_managerClass->resize(800, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/sagiri.png"), QSize(), QIcon::Normal, QIcon::Off);
        canteen_managerClass->setWindowIcon(icon);
        canteen_managerClass->setAutoFillBackground(false);
        centralWidget = new QWidget(canteen_managerClass);
        centralWidget->setObjectName("centralWidget");
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName("stackedWidget");
        loginPage = new QWidget();
        loginPage->setObjectName("loginPage");
        verticalLayout_2 = new QVBoxLayout(loginPage);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_2->addItem(verticalSpacer);

        loginWidget = new QWidget(loginPage);
        loginWidget->setObjectName("loginWidget");
        verticalLayout_3 = new QVBoxLayout(loginWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName("verticalLayout_3");
        titleLabel = new QLabel(loginWidget);
        titleLabel->setObjectName("titleLabel");
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        titleLabel->setFont(font);
        titleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(titleLabel);

        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName("formLayout");
        usernameLabel = new QLabel(loginWidget);
        usernameLabel->setObjectName("usernameLabel");

        formLayout->setWidget(0, QFormLayout::LabelRole, usernameLabel);

        usernameEdit = new QLineEdit(loginWidget);
        usernameEdit->setObjectName("usernameEdit");

        formLayout->setWidget(0, QFormLayout::FieldRole, usernameEdit);

        passwordLabel = new QLabel(loginWidget);
        passwordLabel->setObjectName("passwordLabel");

        formLayout->setWidget(1, QFormLayout::LabelRole, passwordLabel);

        passwordEdit = new QLineEdit(loginWidget);
        passwordEdit->setObjectName("passwordEdit");
        passwordEdit->setEchoMode(QLineEdit::EchoMode::Password);

        formLayout->setWidget(1, QFormLayout::FieldRole, passwordEdit);


        verticalLayout_3->addLayout(formLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        loginButton = new QPushButton(loginWidget);
        loginButton->setObjectName("loginButton");

        horizontalLayout->addWidget(loginButton);

        exitButton = new QPushButton(loginWidget);
        exitButton->setObjectName("exitButton");

        horizontalLayout->addWidget(exitButton);


        verticalLayout_3->addLayout(horizontalLayout);


        verticalLayout_2->addWidget(loginWidget);

        Authorlabel = new QLabel(loginPage);
        Authorlabel->setObjectName("Authorlabel");
        Authorlabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(Authorlabel, 0, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignVCenter);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_2->addItem(verticalSpacer_2);

        stackedWidget->addWidget(loginPage);
        mainPage = new QWidget();
        mainPage->setObjectName("mainPage");
        horizontalLayout_2 = new QHBoxLayout(mainPage);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        navWidget = new QWidget(mainPage);
        navWidget->setObjectName("navWidget");
        navWidget->setMinimumSize(QSize(200, 0));
        navWidget->setMaximumSize(QSize(200, 16777215));
        verticalLayout_4 = new QVBoxLayout(navWidget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName("verticalLayout_4");
        userManageButton = new QPushButton(navWidget);
        userManageButton->setObjectName("userManageButton");

        verticalLayout_4->addWidget(userManageButton);

        canteenManageButton = new QPushButton(navWidget);
        canteenManageButton->setObjectName("canteenManageButton");

        verticalLayout_4->addWidget(canteenManageButton);

        menuManageButton = new QPushButton(navWidget);
        menuManageButton->setObjectName("menuManageButton");

        verticalLayout_4->addWidget(menuManageButton);

        newsManageButton = new QPushButton(navWidget);
        newsManageButton->setObjectName("newsManageButton");

        verticalLayout_4->addWidget(newsManageButton);

        label_2 = new QLabel(navWidget);
        label_2->setObjectName("label_2");
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMinimumSize(QSize(200, 100));
        label_2->setMaximumSize(QSize(200, 100));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/images/nuaalogo.png")));
        label_2->setScaledContents(true);

        verticalLayout_4->addWidget(label_2, 0, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignVCenter);

        label = new QLabel(navWidget);
        label->setObjectName("label");
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(96, 96));
        label->setMaximumSize(QSize(96, 96));
        label->setAutoFillBackground(false);
        label->setPixmap(QPixmap(QString::fromUtf8(":/images/alice.png")));
        label->setScaledContents(true);

        verticalLayout_4->addWidget(label, 0, Qt::AlignmentFlag::AlignHCenter);

        authorlabel = new QLabel(navWidget);
        authorlabel->setObjectName("authorlabel");
        authorlabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_4->addWidget(authorlabel, 0, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignVCenter);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_4->addItem(verticalSpacer_3);

        logoutButton = new QPushButton(navWidget);
        logoutButton->setObjectName("logoutButton");
        logoutButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #f44336;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 5px;\n"
"    border-radius: 3px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #d32f2f;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #b71c1c;\n"
"}"));

        verticalLayout_4->addWidget(logoutButton);


        horizontalLayout_2->addWidget(navWidget);

        contentStackedWidget = new QStackedWidget(mainPage);
        contentStackedWidget->setObjectName("contentStackedWidget");
        canteenPage = new QWidget();
        canteenPage->setObjectName("canteenPage");
        verticalLayout_5 = new QVBoxLayout(canteenPage);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName("verticalLayout_5");
        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setSpacing(6);
        horizontalLayout_21->setObjectName("horizontalLayout_21");
        canteenSearchLabel = new QLabel(canteenPage);
        canteenSearchLabel->setObjectName("canteenSearchLabel");

        horizontalLayout_21->addWidget(canteenSearchLabel);

        canteenSearchEdit = new QLineEdit(canteenPage);
        canteenSearchEdit->setObjectName("canteenSearchEdit");

        horizontalLayout_21->addWidget(canteenSearchEdit);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_21->addItem(horizontalSpacer);


        verticalLayout_5->addLayout(horizontalLayout_21);

        canteenTableView = new QTableView(canteenPage);
        canteenTableView->setObjectName("canteenTableView");

        verticalLayout_5->addWidget(canteenTableView);

        contentStackedWidget->addWidget(canteenPage);
        canteenManagePage = new QWidget();
        canteenManagePage->setObjectName("canteenManagePage");
        verticalLayout_9 = new QVBoxLayout(canteenManagePage);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName("verticalLayout_9");
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        addCanteenButton = new QPushButton(canteenManagePage);
        addCanteenButton->setObjectName("addCanteenButton");

        horizontalLayout_4->addWidget(addCanteenButton);

        editCanteenButton = new QPushButton(canteenManagePage);
        editCanteenButton->setObjectName("editCanteenButton");

        horizontalLayout_4->addWidget(editCanteenButton);

        deleteCanteenButton = new QPushButton(canteenManagePage);
        deleteCanteenButton->setObjectName("deleteCanteenButton");

        horizontalLayout_4->addWidget(deleteCanteenButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        verticalLayout_9->addLayout(horizontalLayout_4);

        searchLayout = new QHBoxLayout();
        searchLayout->setSpacing(6);
        searchLayout->setObjectName("searchLayout");
        searchLabel = new QLabel(canteenManagePage);
        searchLabel->setObjectName("searchLabel");

        searchLayout->addWidget(searchLabel);

        canteenManageSearchEdit = new QLineEdit(canteenManagePage);
        canteenManageSearchEdit->setObjectName("canteenManageSearchEdit");
        canteenManageSearchEdit->setClearButtonEnabled(true);

        searchLayout->addWidget(canteenManageSearchEdit);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        searchLayout->addItem(horizontalSpacer_4);


        verticalLayout_9->addLayout(searchLayout);

        canteenManageTableView = new QTableView(canteenManagePage);
        canteenManageTableView->setObjectName("canteenManageTableView");

        verticalLayout_9->addWidget(canteenManageTableView);

        contentStackedWidget->addWidget(canteenManagePage);
        dishPage = new QWidget();
        dishPage->setObjectName("dishPage");
        verticalLayout_6 = new QVBoxLayout(dishPage);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName("verticalLayout_6");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        dishSearchLabel = new QLabel(dishPage);
        dishSearchLabel->setObjectName("dishSearchLabel");

        horizontalLayout_3->addWidget(dishSearchLabel);

        dishSearchEdit = new QLineEdit(dishPage);
        dishSearchEdit->setObjectName("dishSearchEdit");

        horizontalLayout_3->addWidget(dishSearchEdit);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_6->addLayout(horizontalLayout_3);

        dishContentLayout = new QHBoxLayout();
        dishContentLayout->setSpacing(6);
        dishContentLayout->setObjectName("dishContentLayout");
        dishTableView = new QTableView(dishPage);
        dishTableView->setObjectName("dishTableView");
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(2);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(dishTableView->sizePolicy().hasHeightForWidth());
        dishTableView->setSizePolicy(sizePolicy1);

        dishContentLayout->addWidget(dishTableView);

        dishImageWidget = new QWidget(dishPage);
        dishImageWidget->setObjectName("dishImageWidget");
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(1);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(dishImageWidget->sizePolicy().hasHeightForWidth());
        dishImageWidget->setSizePolicy(sizePolicy2);
        dishImageWidget->setMinimumSize(QSize(300, 0));
        verticalLayout_8 = new QVBoxLayout(dishImageWidget);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName("verticalLayout_8");
        dishImageLabel = new QLabel(dishImageWidget);
        dishImageLabel->setObjectName("dishImageLabel");
        dishImageLabel->setMinimumSize(QSize(280, 280));
        dishImageLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_8->addWidget(dishImageLabel);

        dishNameLabel = new QLabel(dishImageWidget);
        dishNameLabel->setObjectName("dishNameLabel");
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        dishNameLabel->setFont(font1);
        dishNameLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_8->addWidget(dishNameLabel);

        dishPriceLabel = new QLabel(dishImageWidget);
        dishPriceLabel->setObjectName("dishPriceLabel");
        dishPriceLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_8->addWidget(dishPriceLabel);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_8->addItem(verticalSpacer_4);


        dishContentLayout->addWidget(dishImageWidget);


        verticalLayout_6->addLayout(dishContentLayout);

        contentStackedWidget->addWidget(dishPage);
        dishManagePage = new QWidget();
        dishManagePage->setObjectName("dishManagePage");
        verticalLayout_10 = new QVBoxLayout(dishManagePage);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName("verticalLayout_10");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        addDishButton = new QPushButton(dishManagePage);
        addDishButton->setObjectName("addDishButton");

        horizontalLayout_5->addWidget(addDishButton);

        editDishButton = new QPushButton(dishManagePage);
        editDishButton->setObjectName("editDishButton");

        horizontalLayout_5->addWidget(editDishButton);

        deleteDishButton = new QPushButton(dishManagePage);
        deleteDishButton->setObjectName("deleteDishButton");

        horizontalLayout_5->addWidget(deleteDishButton);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);


        verticalLayout_10->addLayout(horizontalLayout_5);

        dishSearchLayout = new QHBoxLayout();
        dishSearchLayout->setSpacing(6);
        dishSearchLayout->setObjectName("dishSearchLayout");
        dishManageSearchLabel = new QLabel(dishManagePage);
        dishManageSearchLabel->setObjectName("dishManageSearchLabel");

        dishSearchLayout->addWidget(dishManageSearchLabel);

        dishManageSearchEdit = new QLineEdit(dishManagePage);
        dishManageSearchEdit->setObjectName("dishManageSearchEdit");
        dishManageSearchEdit->setClearButtonEnabled(true);

        dishSearchLayout->addWidget(dishManageSearchEdit);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        dishSearchLayout->addItem(horizontalSpacer_6);


        verticalLayout_10->addLayout(dishSearchLayout);

        dishManageContentLayout = new QHBoxLayout();
        dishManageContentLayout->setSpacing(6);
        dishManageContentLayout->setObjectName("dishManageContentLayout");
        dishManageTableView = new QTableView(dishManagePage);
        dishManageTableView->setObjectName("dishManageTableView");
        sizePolicy1.setHeightForWidth(dishManageTableView->sizePolicy().hasHeightForWidth());
        dishManageTableView->setSizePolicy(sizePolicy1);

        dishManageContentLayout->addWidget(dishManageTableView);

        dishManageImageWidget = new QWidget(dishManagePage);
        dishManageImageWidget->setObjectName("dishManageImageWidget");
        sizePolicy2.setHeightForWidth(dishManageImageWidget->sizePolicy().hasHeightForWidth());
        dishManageImageWidget->setSizePolicy(sizePolicy2);
        dishManageImageWidget->setMinimumSize(QSize(300, 0));
        verticalLayout_11 = new QVBoxLayout(dishManageImageWidget);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName("verticalLayout_11");
        dishManageImageLabel = new QLabel(dishManageImageWidget);
        dishManageImageLabel->setObjectName("dishManageImageLabel");
        dishManageImageLabel->setMinimumSize(QSize(280, 280));
        dishManageImageLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_11->addWidget(dishManageImageLabel);

        dishManageNameLabel = new QLabel(dishManageImageWidget);
        dishManageNameLabel->setObjectName("dishManageNameLabel");
        dishManageNameLabel->setFont(font1);
        dishManageNameLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_11->addWidget(dishManageNameLabel);

        dishManagePriceLabel = new QLabel(dishManageImageWidget);
        dishManagePriceLabel->setObjectName("dishManagePriceLabel");
        dishManagePriceLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_11->addWidget(dishManagePriceLabel);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_11->addItem(verticalSpacer_5);


        dishManageContentLayout->addWidget(dishManageImageWidget);


        verticalLayout_10->addLayout(dishManageContentLayout);

        contentStackedWidget->addWidget(dishManagePage);
        announcementPage = new QWidget();
        announcementPage->setObjectName("announcementPage");
        verticalLayout_7 = new QVBoxLayout(announcementPage);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName("verticalLayout_7");
        announcementTableView = new QTableView(announcementPage);
        announcementTableView->setObjectName("announcementTableView");

        verticalLayout_7->addWidget(announcementTableView);

        contentStackedWidget->addWidget(announcementPage);
        announcementManagePage = new QWidget();
        announcementManagePage->setObjectName("announcementManagePage");
        verticalLayout_101 = new QVBoxLayout(announcementManagePage);
        verticalLayout_101->setSpacing(6);
        verticalLayout_101->setContentsMargins(11, 11, 11, 11);
        verticalLayout_101->setObjectName("verticalLayout_101");
        horizontalLayout_51 = new QHBoxLayout();
        horizontalLayout_51->setSpacing(6);
        horizontalLayout_51->setObjectName("horizontalLayout_51");
        addAnnouncementButton = new QPushButton(announcementManagePage);
        addAnnouncementButton->setObjectName("addAnnouncementButton");

        horizontalLayout_51->addWidget(addAnnouncementButton);

        editAnnouncementButton = new QPushButton(announcementManagePage);
        editAnnouncementButton->setObjectName("editAnnouncementButton");

        horizontalLayout_51->addWidget(editAnnouncementButton);

        deleteAnnouncementButton = new QPushButton(announcementManagePage);
        deleteAnnouncementButton->setObjectName("deleteAnnouncementButton");

        horizontalLayout_51->addWidget(deleteAnnouncementButton);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_51->addItem(horizontalSpacer_7);


        verticalLayout_101->addLayout(horizontalLayout_51);

        announcementSearchLayout = new QHBoxLayout();
        announcementSearchLayout->setSpacing(6);
        announcementSearchLayout->setObjectName("announcementSearchLayout");
        announcementManageSearchLabel = new QLabel(announcementManagePage);
        announcementManageSearchLabel->setObjectName("announcementManageSearchLabel");

        announcementSearchLayout->addWidget(announcementManageSearchLabel);

        announcementManageSearchEdit = new QLineEdit(announcementManagePage);
        announcementManageSearchEdit->setObjectName("announcementManageSearchEdit");
        announcementManageSearchEdit->setClearButtonEnabled(true);

        announcementSearchLayout->addWidget(announcementManageSearchEdit);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        announcementSearchLayout->addItem(horizontalSpacer_8);


        verticalLayout_101->addLayout(announcementSearchLayout);

        announcementManageTableView = new QTableView(announcementManagePage);
        announcementManageTableView->setObjectName("announcementManageTableView");

        verticalLayout_101->addWidget(announcementManageTableView);

        contentStackedWidget->addWidget(announcementManagePage);
        userManagePage = new QWidget();
        userManagePage->setObjectName("userManagePage");
        verticalLayout_12 = new QVBoxLayout(userManagePage);
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setContentsMargins(11, 11, 11, 11);
        verticalLayout_12->setObjectName("verticalLayout_12");
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        addUserButton = new QPushButton(userManagePage);
        addUserButton->setObjectName("addUserButton");

        horizontalLayout_6->addWidget(addUserButton);

        editUserButton = new QPushButton(userManagePage);
        editUserButton->setObjectName("editUserButton");

        horizontalLayout_6->addWidget(editUserButton);

        deleteUserButton = new QPushButton(userManagePage);
        deleteUserButton->setObjectName("deleteUserButton");

        horizontalLayout_6->addWidget(deleteUserButton);

        resetPasswordButton = new QPushButton(userManagePage);
        resetPasswordButton->setObjectName("resetPasswordButton");

        horizontalLayout_6->addWidget(resetPasswordButton);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_9);


        verticalLayout_12->addLayout(horizontalLayout_6);

        userSearchLayout = new QHBoxLayout();
        userSearchLayout->setSpacing(6);
        userSearchLayout->setObjectName("userSearchLayout");
        userManageSearchLabel = new QLabel(userManagePage);
        userManageSearchLabel->setObjectName("userManageSearchLabel");

        userSearchLayout->addWidget(userManageSearchLabel);

        userManageSearchEdit = new QLineEdit(userManagePage);
        userManageSearchEdit->setObjectName("userManageSearchEdit");
        userManageSearchEdit->setClearButtonEnabled(true);

        userSearchLayout->addWidget(userManageSearchEdit);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        userSearchLayout->addItem(horizontalSpacer_10);


        verticalLayout_12->addLayout(userSearchLayout);

        userManageTableView = new QTableView(userManagePage);
        userManageTableView->setObjectName("userManageTableView");

        verticalLayout_12->addWidget(userManageTableView);

        contentStackedWidget->addWidget(userManagePage);

        horizontalLayout_2->addWidget(contentStackedWidget);

        stackedWidget->addWidget(mainPage);

        verticalLayout->addWidget(stackedWidget);

        canteen_managerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(canteen_managerClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 800, 18));
        canteen_managerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(canteen_managerClass);
        mainToolBar->setObjectName("mainToolBar");
        canteen_managerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(canteen_managerClass);
        statusBar->setObjectName("statusBar");
        canteen_managerClass->setStatusBar(statusBar);

        retranslateUi(canteen_managerClass);

        contentStackedWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(canteen_managerClass);
    } // setupUi

    void retranslateUi(QMainWindow *canteen_managerClass)
    {
        canteen_managerClass->setWindowTitle(QCoreApplication::translate("canteen_managerClass", "\351\243\237\345\240\202\344\277\241\346\201\257\347\256\241\347\220\206\347\263\273\347\273\237", nullptr));
        titleLabel->setText(QCoreApplication::translate("canteen_managerClass", "\351\243\237\345\240\202\344\277\241\346\201\257\347\256\241\347\220\206\347\263\273\347\273\237", nullptr));
        usernameLabel->setText(QCoreApplication::translate("canteen_managerClass", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        passwordLabel->setText(QCoreApplication::translate("canteen_managerClass", "\345\257\206\347\240\201\357\274\232", nullptr));
        loginButton->setText(QCoreApplication::translate("canteen_managerClass", "\347\231\273\345\275\225", nullptr));
        exitButton->setText(QCoreApplication::translate("canteen_managerClass", "\351\200\200\345\207\272", nullptr));
        Authorlabel->setText(QCoreApplication::translate("canteen_managerClass", "BY 162310119\347\216\213\345\271\277\346\240\213", nullptr));
        userManageButton->setText(QCoreApplication::translate("canteen_managerClass", "\347\224\250\346\210\267\347\256\241\347\220\206", nullptr));
        canteenManageButton->setText(QCoreApplication::translate("canteen_managerClass", "\351\243\237\345\240\202\347\256\241\347\220\206", nullptr));
        menuManageButton->setText(QCoreApplication::translate("canteen_managerClass", "\350\217\234\350\260\261\347\256\241\347\220\206", nullptr));
        newsManageButton->setText(QCoreApplication::translate("canteen_managerClass", "\346\226\260\351\227\273\345\205\254\345\221\212", nullptr));
        label_2->setText(QString());
        label->setText(QString());
        authorlabel->setText(QCoreApplication::translate("canteen_managerClass", "<html><head/><body><p>BY 162310119\347\216\213\345\271\277\346\240\213</p></body></html>", nullptr));
        logoutButton->setText(QCoreApplication::translate("canteen_managerClass", "\351\200\200\345\207\272\347\231\273\345\275\225", nullptr));
        canteenSearchLabel->setText(QCoreApplication::translate("canteen_managerClass", "\346\220\234\347\264\242\357\274\232", nullptr));
        canteenSearchEdit->setPlaceholderText(QCoreApplication::translate("canteen_managerClass", "\350\276\223\345\205\245\351\243\237\345\240\202\345\220\215\347\247\260\346\210\226\344\275\215\347\275\256\346\220\234\347\264\242...", nullptr));
        addCanteenButton->setText(QCoreApplication::translate("canteen_managerClass", "\346\267\273\345\212\240\351\243\237\345\240\202", nullptr));
        editCanteenButton->setText(QCoreApplication::translate("canteen_managerClass", "\347\274\226\350\276\221\351\243\237\345\240\202", nullptr));
        deleteCanteenButton->setText(QCoreApplication::translate("canteen_managerClass", "\345\210\240\351\231\244\351\243\237\345\240\202", nullptr));
        searchLabel->setText(QCoreApplication::translate("canteen_managerClass", "\346\220\234\347\264\242\357\274\232", nullptr));
        canteenManageSearchEdit->setPlaceholderText(QCoreApplication::translate("canteen_managerClass", "\350\276\223\345\205\245\351\243\237\345\240\202\345\220\215\347\247\260\346\210\226\344\275\215\347\275\256\346\220\234\347\264\242...", nullptr));
        dishSearchLabel->setText(QCoreApplication::translate("canteen_managerClass", "\346\220\234\347\264\242\357\274\232", nullptr));
        dishSearchEdit->setPlaceholderText(QCoreApplication::translate("canteen_managerClass", "\350\276\223\345\205\245\350\217\234\345\223\201\345\220\215\347\247\260\346\210\226\346\211\200\345\261\236\351\243\237\345\240\202\346\220\234\347\264\242...", nullptr));
        dishImageLabel->setStyleSheet(QCoreApplication::translate("canteen_managerClass", "border: 1px solid #cccccc;\n"
"background-color: white;", nullptr));
        dishImageLabel->setText(QCoreApplication::translate("canteen_managerClass", "\346\232\202\346\227\240\345\233\276\347\211\207", nullptr));
        dishNameLabel->setText(QString());
        dishPriceLabel->setStyleSheet(QCoreApplication::translate("canteen_managerClass", "color: #e74c3c;", nullptr));
        dishPriceLabel->setText(QString());
        addDishButton->setText(QCoreApplication::translate("canteen_managerClass", "\346\267\273\345\212\240\350\217\234\345\223\201", nullptr));
        editDishButton->setText(QCoreApplication::translate("canteen_managerClass", "\347\274\226\350\276\221\350\217\234\345\223\201", nullptr));
        deleteDishButton->setText(QCoreApplication::translate("canteen_managerClass", "\345\210\240\351\231\244\350\217\234\345\223\201", nullptr));
        dishManageSearchLabel->setText(QCoreApplication::translate("canteen_managerClass", "\346\220\234\347\264\242\357\274\232", nullptr));
        dishManageSearchEdit->setPlaceholderText(QCoreApplication::translate("canteen_managerClass", "\350\276\223\345\205\245\350\217\234\345\223\201\345\220\215\347\247\260\346\210\226\346\211\200\345\261\236\351\243\237\345\240\202\346\220\234\347\264\242...", nullptr));
        dishManageImageLabel->setStyleSheet(QCoreApplication::translate("canteen_managerClass", "border: 1px solid #cccccc;\n"
"background-color: white;", nullptr));
        dishManageImageLabel->setText(QCoreApplication::translate("canteen_managerClass", "\346\232\202\346\227\240\345\233\276\347\211\207", nullptr));
        dishManageNameLabel->setText(QString());
        dishManagePriceLabel->setStyleSheet(QCoreApplication::translate("canteen_managerClass", "color: #e74c3c;", nullptr));
        dishManagePriceLabel->setText(QString());
        addAnnouncementButton->setText(QCoreApplication::translate("canteen_managerClass", "\346\267\273\345\212\240\345\205\254\345\221\212", nullptr));
        editAnnouncementButton->setText(QCoreApplication::translate("canteen_managerClass", "\347\274\226\350\276\221\345\205\254\345\221\212", nullptr));
        deleteAnnouncementButton->setText(QCoreApplication::translate("canteen_managerClass", "\345\210\240\351\231\244\345\205\254\345\221\212", nullptr));
        announcementManageSearchLabel->setText(QCoreApplication::translate("canteen_managerClass", "\346\220\234\347\264\242\357\274\232", nullptr));
        announcementManageSearchEdit->setPlaceholderText(QCoreApplication::translate("canteen_managerClass", "\350\276\223\345\205\245\346\240\207\351\242\230\346\210\226\345\206\205\345\256\271\346\220\234\347\264\242...", nullptr));
        addUserButton->setText(QCoreApplication::translate("canteen_managerClass", "\346\267\273\345\212\240\347\224\250\346\210\267", nullptr));
        editUserButton->setText(QCoreApplication::translate("canteen_managerClass", "\347\274\226\350\276\221\347\224\250\346\210\267", nullptr));
        deleteUserButton->setText(QCoreApplication::translate("canteen_managerClass", "\345\210\240\351\231\244\347\224\250\346\210\267", nullptr));
        resetPasswordButton->setText(QCoreApplication::translate("canteen_managerClass", "\351\207\215\347\275\256\345\257\206\347\240\201", nullptr));
        userManageSearchLabel->setText(QCoreApplication::translate("canteen_managerClass", "\346\220\234\347\264\242\357\274\232", nullptr));
        userManageSearchEdit->setPlaceholderText(QCoreApplication::translate("canteen_managerClass", "\350\276\223\345\205\245\347\224\250\346\210\267\345\220\215\343\200\201\347\224\265\350\257\235\346\210\226\351\202\256\347\256\261\346\220\234\347\264\242...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class canteen_managerClass: public Ui_canteen_managerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CANTEEN_MANAGER_H
