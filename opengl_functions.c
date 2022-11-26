int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(960, 640);
	glutInitWindowPosition(glutGet(GLUT_SCREEN_WIDTH) / 2 - 960 / 2, glutGet(GLUT_SCREEN_HEIGHT) / 2 - 640 / 2);
	glutCreateWindow("The Maze project");
	gluOrtho2D(0, 960, 640, 0);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(ButtonDown);
	glutKeyboardUpFunc(ButtonUp);
	glutMainLoop();
}
