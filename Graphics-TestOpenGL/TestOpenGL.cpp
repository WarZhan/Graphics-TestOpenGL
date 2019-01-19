#include "Angel.h"

// 程序运行时弹出的命令控制台窗口主要用于输出相关信息，比如shader的编译和链接信息，在程序完成后发布时可让其不再弹出
//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

typedef vec2 point2;

void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT); // 使用背景色擦除窗口
	// 使用顶点数组数据进行绘制
	glDrawArrays(
		GL_TRIANGLES,	// 绘制图元为三角形
		0,				// 顶点数组起始索引
		6);				// 绘制顶点数量（即画 2 个三角形， 注意这里不是三角形个数）

	glFlush(); // 使缓存的绘图指令立即执行
}

void Init()
{
	// 顶点数据
	point2 vertices[6] =
	{
		point2(-0.5, -0.5), point2(0.5, -0.5), point2(-0.5, 0.5),	// 第一个三角形
		point2(-0.5, 0.5), point2(0.5, -0.5), point2(0.5, 0.5),		// 第二个三角形
	};

	// 创建一个顶点数组对象 VAO vertex_array_object
	GLuint vao;
	glGenVertexArrays(1, &vao); // 生成一个未用的 VAO ID，存于 vao 中
	glBindVertexArray(vao);		// 创建 id 为 vao 的 VAO，并绑定为当前 VAO

	// 创建并初始化一个缓冲区对象（Buffer Object）
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer); // 创建 id 为 buffer 的 Array Buffer 对象，并绑定为单前 Array Buffer 对象

	// 为 Buffer 对象在 GPU 端申请空间，并提供数据
	glBufferData(GL_ARRAY_BUFFER,	// Buffer 类型
		sizeof(vertices),			// 申请空间大小（以字节为单位）
		vertices,					//  数据指针
		GL_STATIC_DRAW);			// 表明将如何使用 Buffer 的标志（GL_STATIC_DRAW ：一次提供数据，多次绘制）

	// 初始化 shader
	GLuint program = InitShader("vSimple.glsl", "fSimple.glsl");
	glUseProgram(program);

	// 获取 shader 程序中变量地址
	GLuint loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(loc); // 启用顶点属性数组

	// 为顶点属性数组提供数据（数据存放在之前 buffer 对象中）
	glVertexAttribPointer(
		loc,		// 属性变量索引
		2,			// 每个顶点属性的分量个数
		GL_FLOAT,	// 数组数据类型
		GL_FALSE,	// 是否进行归一化
		0,			// 在数组中相邻属性成员间的间隔（以字节为单位）
		BUFFER_OFFSET(0)); // 第一个属性值在 buffer 中的偏移量

	glClearColor(0.0, 0.0, 0.0, 1.0); // 指定背景刷新颜色
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	// 以下窗口初始化 属性 和 上下文（Context）的函数必须在 glutCreateWindow 前调用
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);

	glutInitContextVersion(3, 1); // 指定 OpengGL 3.1

	// 保持先前兼容，即不使用任何废弃的
	// 如程序中使用了弃用函数则注释本行
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	// OpenGL 3.2 以上版本才有效果，作用和 glutInitContextFlags 类似
	//glutInitContextProfile(GLUT_CORE_PROFILE);

	glutCreateWindow("Simple");

	// 显卡驱动非正式发布版 或者 与 glew 库 规范不兼容时加上此行
	// 如果在 glGenVertexArrays 处发生 Access Violation 则加上此行
	glewExperimental = GL_TRUE;

	GLenum err = glewInit(); // 初始化 glew 库，必须在 glutCreateWindow 之后调用
	if (err != GLEW_OK)
	{
		std::cout << "glewInit fault !! " << std::endl;
		exit(EXIT_FAILURE);
	}

	// 注册显示回调函数 必须有
	glutDisplayFunc(MyDisplay);

	Init();

	glutMainLoop();

	return 0;
}
