#include "Angel.h"

// ��������ʱ�������������̨������Ҫ������������Ϣ������shader�ı����������Ϣ���ڳ�����ɺ󷢲�ʱ�����䲻�ٵ���
//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

typedef vec2 point2;

void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT); // ʹ�ñ���ɫ��������
	// ʹ�ö����������ݽ��л���
	glDrawArrays(
		GL_TRIANGLES,	// ����ͼԪΪ������
		0,				// ����������ʼ����
		6);				// ���ƶ������������� 2 �������Σ� ע�����ﲻ�������θ�����

	glFlush(); // ʹ����Ļ�ͼָ������ִ��
}

void Init()
{
	// ��������
	point2 vertices[6] =
	{
		point2(-0.5, -0.5), point2(0.5, -0.5), point2(-0.5, 0.5),	// ��һ��������
		point2(-0.5, 0.5), point2(0.5, -0.5), point2(0.5, 0.5),		// �ڶ���������
	};

	// ����һ������������� VAO vertex_array_object
	GLuint vao;
	glGenVertexArrays(1, &vao); // ����һ��δ�õ� VAO ID������ vao ��
	glBindVertexArray(vao);		// ���� id Ϊ vao �� VAO������Ϊ��ǰ VAO

	// ��������ʼ��һ������������Buffer Object��
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer); // ���� id Ϊ buffer �� Array Buffer ���󣬲���Ϊ��ǰ Array Buffer ����

	// Ϊ Buffer ������ GPU ������ռ䣬���ṩ����
	glBufferData(GL_ARRAY_BUFFER,	// Buffer ����
		sizeof(vertices),			// ����ռ��С�����ֽ�Ϊ��λ��
		vertices,					//  ����ָ��
		GL_STATIC_DRAW);			// ���������ʹ�� Buffer �ı�־��GL_STATIC_DRAW ��һ���ṩ���ݣ���λ��ƣ�

	// ��ʼ�� shader
	GLuint program = InitShader("vSimple.glsl", "fSimple.glsl");
	glUseProgram(program);

	// ��ȡ shader �����б�����ַ
	GLuint loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(loc); // ���ö�����������

	// Ϊ�������������ṩ���ݣ����ݴ����֮ǰ buffer �����У�
	glVertexAttribPointer(
		loc,		// ���Ա�������
		2,			// ÿ���������Եķ�������
		GL_FLOAT,	// ������������
		GL_FALSE,	// �Ƿ���й�һ��
		0,			// ���������������Գ�Ա��ļ�������ֽ�Ϊ��λ��
		BUFFER_OFFSET(0)); // ��һ������ֵ�� buffer �е�ƫ����

	glClearColor(0.0, 0.0, 0.0, 1.0); // ָ������ˢ����ɫ
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	// ���´��ڳ�ʼ�� ���� �� �����ģ�Context���ĺ��������� glutCreateWindow ǰ����
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);

	glutInitContextVersion(3, 1); // ָ�� OpengGL 3.1

	// ������ǰ���ݣ�����ʹ���κη�����
	// �������ʹ�������ú�����ע�ͱ���
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	// OpenGL 3.2 ���ϰ汾����Ч�������ú� glutInitContextFlags ����
	//glutInitContextProfile(GLUT_CORE_PROFILE);

	glutCreateWindow("Simple");

	// �Կ���������ʽ������ ���� �� glew �� �淶������ʱ���ϴ���
	// ����� glGenVertexArrays ������ Access Violation ����ϴ���
	glewExperimental = GL_TRUE;

	GLenum err = glewInit(); // ��ʼ�� glew �⣬������ glutCreateWindow ֮�����
	if (err != GLEW_OK)
	{
		std::cout << "glewInit fault !! " << std::endl;
		exit(EXIT_FAILURE);
	}

	// ע����ʾ�ص����� ������
	glutDisplayFunc(MyDisplay);

	Init();

	glutMainLoop();

	return 0;
}
