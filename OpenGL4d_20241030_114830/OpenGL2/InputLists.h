#pragma once
static int transform_input(char input)
{
	switch (input) 
	{
	case 'a':return GLFW_KEY_A;break;
	case 'A':return GLFW_KEY_A;break;

	case 'b':return GLFW_KEY_B;break;
	case 'B':return GLFW_KEY_B;break;

	case 'c':return GLFW_KEY_C;break;
	case 'C':return GLFW_KEY_C;break;

	case 'd':return GLFW_KEY_D;break;
	case 'D':return GLFW_KEY_D;break;

	case 'e':return GLFW_KEY_E;break;
	case 'E':return GLFW_KEY_E;break;

	case 'f':return GLFW_KEY_F;break;
	case 'F':return GLFW_KEY_F;break;

	case 'g':return GLFW_KEY_G;break;
	case 'G':return GLFW_KEY_G;break;

	case 'h':return GLFW_KEY_H;break;
	case 'H':return GLFW_KEY_H;break;

	case 'i':return GLFW_KEY_I;break;
	case 'I':return GLFW_KEY_I;break;

	case 'j':return GLFW_KEY_J;break;
	case 'J':return GLFW_KEY_J;break;

	case 'k':return GLFW_KEY_K;break;
	case 'K':return GLFW_KEY_K;break;

	case 'l':return GLFW_KEY_L;break;
	case 'L':return GLFW_KEY_L;break;

	case 'm':return GLFW_KEY_M;break;
	case 'M':return GLFW_KEY_M;break;

	case 'n':return GLFW_KEY_N;break;
	case 'N':return GLFW_KEY_N;break;

	case 'o':return GLFW_KEY_O;break;
	case 'O':return GLFW_KEY_O;break;

	case 'p':return GLFW_KEY_P;break;
	case 'P':return GLFW_KEY_P;break;

	case 'q':return GLFW_KEY_Q;break;
	case 'Q':return GLFW_KEY_Q;break;

	case 'r':return GLFW_KEY_R;break;
	case 'R':return GLFW_KEY_R;break;

	case 's':return GLFW_KEY_S;break;
	case 'S':return GLFW_KEY_S;break;

	case 't':return GLFW_KEY_T;break;
	case 'T':return GLFW_KEY_T;break;

	case 'u':return GLFW_KEY_U;break;
	case 'U':return GLFW_KEY_U;break;

	case 'v':return GLFW_KEY_V;break;
	case 'V':return GLFW_KEY_V;break;

	case 'w':return GLFW_KEY_W;break;
	case 'W':return GLFW_KEY_W;break;

	case 'x':return GLFW_KEY_X;break;
	case 'X':return GLFW_KEY_X;break;

	case 'y':return GLFW_KEY_Y;break;
	case 'Y':return GLFW_KEY_Y;break;

	case 'z':return GLFW_KEY_Z;break;
	case 'Z':return GLFW_KEY_Z;break;

	case '1':return GLFW_KEY_1;break;
	case '2':return GLFW_KEY_2;break;

	case '3':return GLFW_KEY_3;break;
	case '4':return GLFW_KEY_4;break;

	case '5':return GLFW_KEY_5;break;
	case '6':return GLFW_KEY_6;break;

	case '7':return GLFW_KEY_7;break;
	case '8':return GLFW_KEY_8;break;

	case '9':return GLFW_KEY_9;break;
	case '0':return GLFW_KEY_0;break;

	case ' ':return GLFW_KEY_SPACE; break;
	}
}