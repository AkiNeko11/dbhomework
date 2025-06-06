-- 创建数据库
DROP DATABASE IF EXISTS canteen_management;
CREATE DATABASE canteen_management;
USE canteen_management;

-- 用户表
CREATE TABLE users (
    user_id INT PRIMARY KEY AUTO_INCREMENT,
    username VARCHAR(50) UNIQUE NOT NULL,
    password VARCHAR(255) NOT NULL,
    phone VARCHAR(20),
    address VARCHAR(255),
    gender ENUM('M', 'F', 'O'),
    email VARCHAR(100),
    user_type ENUM('admin', 'user') NOT NULL DEFAULT 'user',
    status ENUM('active', 'inactive') DEFAULT 'active',
    last_login TIMESTAMP,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- 食堂表
CREATE TABLE canteens (
    canteen_id INT PRIMARY KEY AUTO_INCREMENT,
    canteen_name VARCHAR(100) NOT NULL,
    description TEXT,
    location VARCHAR(255),
    opening_hours VARCHAR(100),
    status ENUM('open', 'closed', 'renovating') DEFAULT 'open',
    rating DECIMAL(2,1) DEFAULT 5.0,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- 菜品表
CREATE TABLE dishes (
    dish_id INT PRIMARY KEY AUTO_INCREMENT,
    canteen_id INT NOT NULL,
    dish_name VARCHAR(100) NOT NULL,
    description TEXT,
    price DECIMAL(10,2) NOT NULL,
    category VARCHAR(50),
    is_available BOOLEAN DEFAULT TRUE,
    image_path VARCHAR(255),
    sales_count INT DEFAULT 0,
    rating DECIMAL(2,1) DEFAULT 5.0,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    FOREIGN KEY (canteen_id) REFERENCES canteens(canteen_id) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- 公告表
CREATE TABLE announcements (
    announcement_id INT PRIMARY KEY AUTO_INCREMENT,
    title VARCHAR(200) NOT NULL,
    content TEXT NOT NULL,
    publisher_id INT NOT NULL,
    publish_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    is_active BOOLEAN DEFAULT TRUE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    FOREIGN KEY (publisher_id) REFERENCES users(user_id) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- 权限表
CREATE TABLE permissions (
    permission_id INT PRIMARY KEY AUTO_INCREMENT,
    user_id INT NOT NULL,
    can_manage_users BOOLEAN DEFAULT FALSE,
    can_manage_canteens BOOLEAN DEFAULT FALSE,
    can_manage_dishes BOOLEAN DEFAULT FALSE,
    can_manage_announcements BOOLEAN DEFAULT FALSE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users(user_id) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;


-- 操作日志表
CREATE TABLE operation_logs (
    log_id INT PRIMARY KEY AUTO_INCREMENT,
    user_id INT NOT NULL,
    operation_type ENUM('insert', 'update', 'delete') NOT NULL,
    table_name VARCHAR(50) NOT NULL,
    record_id INT NOT NULL,
    operation_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    details TEXT,
    FOREIGN KEY (user_id) REFERENCES users(user_id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- 创建触发器
DELIMITER //

-- 用户操作日志触发器
CREATE TRIGGER after_user_change
AFTER UPDATE ON users
FOR EACH ROW
BEGIN
    INSERT INTO operation_logs (user_id, operation_type, table_name, record_id, details)
    VALUES (NEW.user_id, 'update', 'users', NEW.user_id, 
            CONCAT('用户信息更新: ', OLD.username, ' -> ', NEW.username));
END //

-- 菜品评分更新触发器
CREATE TRIGGER after_review_insert
AFTER INSERT ON reviews
FOR EACH ROW
BEGIN
    UPDATE dishes 
    SET rating = (
        SELECT AVG(rating) 
        FROM reviews 
        WHERE dish_id = NEW.dish_id
    )
    WHERE dish_id = NEW.dish_id;
END //

DELIMITER ;

-- 创建视图
-- 食堂信息视图
CREATE OR REPLACE VIEW canteens_view AS
SELECT 
    canteen_id,
    canteen_name,
    description,
    location,
    opening_hours,
    status,
    rating
FROM canteens;

-- 菜品信息视图
CREATE OR REPLACE VIEW dishes_view AS
SELECT 
    d.dish_id,
    c.canteen_name,
    d.dish_name,
    d.description,
    d.price,
    d.category,
    d.is_available,
    d.sales_count,
    d.rating,
    d.image_path
FROM dishes d
JOIN canteens c ON d.canteen_id = c.canteen_id;

-- 公告信息视图
CREATE OR REPLACE VIEW announcements_view AS
SELECT 
    a.announcement_id,
    a.title,
    a.content,
    u.username as publisher,
    a.publish_date,
    a.created_at,
    a.updated_at
FROM announcements a
JOIN users u ON a.publisher_id = u.user_id
WHERE a.is_active = TRUE
ORDER BY a.publish_date DESC;

-- 用户信息视图
CREATE OR REPLACE VIEW users_view AS
SELECT 
    user_id,
    username,
    CASE gender
        WHEN 'M' THEN '男'
        WHEN 'F' THEN '女'
        WHEN 'O' THEN '其他'
        ELSE '未设置'
    END as gender_text,
    phone,
    email,
    address,
    CASE user_type
        WHEN 'admin' THEN '管理员'
        WHEN 'user' THEN '普通用户'
    END as user_type_text,
    CASE status
        WHEN 'active' THEN '正常'
        WHEN 'inactive' THEN '已禁用'
    END as status_text,
    last_login,
    created_at,
    updated_at
FROM users
ORDER BY created_at DESC;

-- 创建存储过程
DELIMITER //

-- 添加新菜品的存储过程
CREATE PROCEDURE sp_add_dish(
    IN p_canteen_id INT,
    IN p_dish_name VARCHAR(100),
    IN p_description TEXT,
    IN p_price DECIMAL(10,2),
    IN p_category VARCHAR(50),
    IN p_image_path VARCHAR(255)
)
BEGIN
    INSERT INTO dishes (
        canteen_id, dish_name, description, 
        price, category, image_path
    ) VALUES (
        p_canteen_id, p_dish_name, p_description, 
        p_price, p_category, p_image_path
    );
END //

-- 用户权限检查存储过程
CREATE PROCEDURE sp_check_permission(
    IN p_user_id INT,
    IN p_permission_type VARCHAR(50),
    OUT p_has_permission BOOLEAN
)
BEGIN
    SELECT 
        CASE p_permission_type
            WHEN 'users' THEN can_manage_users
            WHEN 'canteens' THEN can_manage_canteens
            WHEN 'dishes' THEN can_manage_dishes
            WHEN 'announcements' THEN can_manage_announcements
            ELSE FALSE
        END INTO p_has_permission
    FROM permissions
    WHERE user_id = p_user_id;
END //

DELIMITER ;

