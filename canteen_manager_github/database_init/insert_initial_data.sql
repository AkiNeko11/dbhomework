USE canteen_management;

-- 插入用户数据
INSERT INTO users (username, password, user_type, status, phone, address, gender, email) 
VALUES 
('admin123', 'admin123', 'admin', 'active', '12300000000', '天目湖校区', 'M', 'admin123@canteen.com'),
('user1', 'user1', 'user', 'active', '12311111111', '天目湖校区', 'M', 'user1@canteen.com');

-- 插入管理员权限
INSERT INTO permissions (user_id, can_manage_users, can_manage_canteens, can_manage_dishes, can_manage_announcements)
SELECT user_id, TRUE, TRUE, TRUE, TRUE 
FROM users 
WHERE username = 'admin123';

-- 插入食堂数据
INSERT INTO canteens (canteen_name, description, location, opening_hours, status, rating) 
VALUES 
('东篱苑', '主要提供中式快餐，价格实惠，菜品丰富', '天目湖校区东区', '6:30-20:00', 'open', 4.5),
('南山苑', '特色面食和西式快餐，环境优雅', '天目湖校区南区', '6:30-20:00', 'open', 4.8);

-- 插入菜品数据
INSERT INTO dishes (canteen_id, dish_name, description, price, category, is_available, sales_count, rating) 
VALUES 
(1, '红烧肉', '传统美食，肥而不腻', 10.00, '荤菜', TRUE, 0, 5.0),
(1, '清酒南瓜', '新鲜时令蔬菜', 4.00, '素菜', TRUE, 0, 5.0),
(2, '牛肉面', '现煮面条配上新鲜牛肉', 15.00, '面食', TRUE, 0, 5.0),
(2, '猪脚饭', '广式经典风味', 16.00, '套餐', TRUE, 0, 5.0);

-- 插入公告数据
INSERT INTO announcements (title, content, publisher_id, publish_date, is_active) 
SELECT 
    '营业时间调整通知',
    '因设备维护，东篱苑将于本周六暂停营业一天，请同学们合理安排就餐时间。',
    user_id,
    NOW(),
    TRUE
FROM users 
WHERE username = 'admin123';

INSERT INTO announcements (title, content, publisher_id, publish_date, is_active)
SELECT 
    '新菜品上线公告',
    '南山苑新增多款特色面点，欢迎同学们前来品尝！',
    user_id,
    DATE_SUB(NOW(), INTERVAL 1 DAY),
    TRUE
FROM users 
WHERE username = 'admin123';

