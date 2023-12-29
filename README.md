# 正点原子Qt开发指南 
正点原子Qt开发指南 

## 信号与槽

## Qt 控件

### 按钮

- QPushButton:下压按钮 **通常用于执行命令 或触发事件。**
-  QToolButton:工具按钮 **是一种用于命令或者选项的可以快速访问的按钮， 通常在 ToolBar 里面。**
- QRadioButton:选择按钮 **RadioButton 单选按钮（单选框）通常成组出现， 用于提供两个或多个互斥选项。**
- QCheckBox:检查框 **复选按钮（复选框）与 RadioButton 的区别是选择模式，单选按钮提供多选一，复选按钮提供多选多。**
-  QCommandLinkButton:命令链接按钮 **都是用于在互斥选项中选择一项，它也将携带一个箭头图标，表明按下按钮将打开另一个窗口或页面。**
- QDialogButtonBox:对话框按钮 **常用于对话框里自定义按钮，比如“确定”和“取消”按钮。**

### 输入窗口部件

- Comb Box:组合框 **通常用于用户显示选项列表的 方法，这种方法占用最少的屏幕空间。**
- Font Comb Box:字体组合框 **允许用户选择字体系列的组合框**
- Line Edit:单行编辑框 **一个单行文本编辑器，通过更 改行编辑的 echoMode()，它还可以用作“只写”字段，用于输入如密码等。**
- Text Edit:文本编辑框  **一个高级所见即 所得查看器/编辑器，支持使用 html 样式的标记进行 rich text 格式化**
- Plain Text Edit:纯文本编辑框 **一个支持纯文本的高级查看器/编辑器。它被优化为处理大型文档和快速 响应用户输入**
- Spin Box:数字旋转框 **用于处理整数和离散值，允许用户通过单击上/下按钮或按下键盘上的上/下按钮来选择一个值，以增加/减少当 前显示的值**
- Double Spin Box:双精度数字旋转框 **用于处理浮点值，允许用户通过单击“向上”和“向下”按钮或按下键盘上的“向上”或“向下”按钮来 选择当前显示的值**
- Time Edit:时间编辑框 **用于编辑时间**
- Date Edit:日期编辑框 **用于编辑日期**
- Date/Time Edit:日期时间编辑框 **用于编辑日期和时间**
- Dial:数字拨盘框 **提供了一个圆形范围控制(如速度计或电位器**
- Horizontal Scroll Bar:水平滚动条 **提供垂直滚动条**
- Vertical Scroll Bar:垂直滚动条 **提供水平滚动条**
- Horizontal Slider:水平滑动条 **提供垂直滑动条小部件**
- Vertical Slider:垂直滑动条 **提供水平滑动条小部件**
-  Key sequence Edit:按键序列编辑框 **通常用作记录快捷键**

### 显示窗口部件

- Label:标签 **用于文本或图像显示的小部件**
- Text Browser:文本浏览器 **提供了一个具有超文本导航的文本浏览器。**
- Graphics View:图形视图 **提 供了基于图元的模型/视图编程。QGraphicsView 在可滚动视图中可视化 QGraphicsScene 的内容**
- Calendar Widget:日历**提供了一个基于月的日历小部件，允许用户选择日期**
-  LCD Number:液晶数字 **显示一个类似于 lcd 的数字**
- Progress Bar:进度条 **提供了一个水平或垂直的进度条**
- Horizontal Line:水平线
- Vertial Line:垂直线
- OpenGL Widget:开放式图形库工具
- QQuick Widget:嵌入式 QML 工具

### 布局管理

-  Vertiacl Layout:垂直布局
-  Horizontal Layout:水平布局
-  Grid Layout:网格布局 **获取可用的空间，将其分为行和列，并将其管理的每个小部件放入正确的单元格中**
-  Form Layout:表单布局 **管理输入小部件及其关联标签的表单**

## 文本读写

## 绘图与图表

## 多线程

## 网络编程

## 数据库



