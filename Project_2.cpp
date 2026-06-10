#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

enum enQuestionsLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };
enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };

int RandomNumber(int From, int To)
{
	//Function to generate a random number
	int random = rand() % (To - From + 1) + From;
	return random;
}

string GetOpTypeSymbol(enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return "+";
	case enOperationType::Sub:
		return "-";
	case enOperationType::Mult:
		return "*";
	case enOperationType::Div:
		return "/";
	default:
		return "+";
	}
}

string GetQuestionLevelText(enQuestionsLevel QuestionLevel)
{

	string arrQuestionLevelText[4] = { "Easy", "Med","Hard", "Mix" };
	return arrQuestionLevelText[QuestionLevel - 1];

}

int ReadHowManyQuestions()
{
	short NumberOfQuestions;

	do
	{
		cout << "How Many Questions do you want to answer ? ";
		cin >> NumberOfQuestions;

	} while (NumberOfQuestions < 1 || NumberOfQuestions > 10);

	return NumberOfQuestions;

}

enQuestionsLevel ReadQuestionsLevel()
{
	short QuestionsLevel = 0;

	do
	{
		cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
		cin >> QuestionsLevel;

	} while (QuestionsLevel < 1 || QuestionsLevel > 4);

	return (enQuestionsLevel)QuestionsLevel;
}

enOperationType ReadOpType()
{
	short OpType = 0;

	do
	{
		cout << "Enter Operations Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
		cin >> OpType;

	} while (OpType < 1 || OpType > 5);

	return (enOperationType)OpType;
}

struct stQuestion
{
	int Number1 = 0;
	int Number2 = 0;
	enOperationType OperationType;
	enQuestionsLevel QuestionLevel;
	int CorrectAnswer = 0;
	int PlayerAnswer = 0;
	bool AnswerResult = false;
};

struct stQuizz
{
	stQuestion QuestionList[100];
	short NumberOfQuestion;
	enQuestionsLevel QuestionsLevel;
	enOperationType OpType;
	short NumberOfWrongAnswer = 0;
	short NumberOfRightAnswer = 0;
	bool isPass = false;
};

int SimpleCalculator(int Number1, int Number2, enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return Number1 + Number2;
	case enOperationType::Sub:
		return Number1 - Number2;
	case enOperationType::Mult:
		return Number1 * Number2;
	case enOperationType::Div:
		return Number1 / Number2;
	default:
		return Number1 + Number2;
	}
}

enOperationType GetRandomOperation()
{
	int Op = RandomNumber(1, 4);
	return (enOperationType)Op;
}

stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel, enOperationType OpType)
{
	stQuestion Question;

	if (QuestionLevel == enQuestionsLevel::Mix)
	{
		QuestionLevel = (enQuestionsLevel)RandomNumber(1, 3);
	}

	if (OpType == enOperationType::MixOp)
	{
		OpType = GetRandomOperation();
	}

	Question.OperationType = OpType;

	switch (QuestionLevel)
	{
	case enQuestionsLevel::EasyLevel:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;

	case enQuestionsLevel::MedLevel:
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;

	case enQuestionsLevel::HardLevel:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;
	}

	return Question;
}

void GenerateQuizzQuestions(stQuizz& Quizz)
{
	for (short Question = 0; Question < Quizz.NumberOfQuestion; Question++)
	{
		Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.OpType);
	}
}

int ReadQuestionAnswer()
{

	int Number;
	cin >> Number;
	return Number;

}

void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber)
{

	cout << "\nQuestion [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestion << "]\n\n";
	cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
	cout << Quizz.QuestionList[QuestionNumber].Number2 << " ";
	cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType);
	cout << "\n____________" << endl;

}

void SetScreenColor(bool AnswerResult)
{
	if (AnswerResult)
		system("color 2F");
	else
	{
		system("color 4F");
		cout << "\a";
	}
}

void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
	if (Quizz.QuestionList[QuestionNumber].CorrectAnswer != Quizz.QuestionList[QuestionNumber].PlayerAnswer)
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = false;
		Quizz.NumberOfWrongAnswer++;

		cout << "Wrong Answer :-( \n";
		cout << "The right answer is: ";
		cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer;
		cout << "\n";
	}
	else
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = true;
		Quizz.NumberOfRightAnswer++;

		cout << "Right answer :-)\n";
	}

	SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);

}

void AskAndCorrectQuestionListAnswer(stQuizz& Quizz)
{
	
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestion; QuestionNumber++)
	{

		PrintTheQuestion(Quizz, QuestionNumber);
		Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();
		CorrectTheQuestionAnswer(Quizz, QuestionNumber);

	}

	Quizz.isPass = (Quizz.NumberOfRightAnswer >= Quizz.NumberOfWrongAnswer);

	/*if (Quizz.NumberOfRightAnswer >= Quizz.NumberOfWrongAnswer)
	{
		Quizz.isPass = true;
	}
	else
	{
		Quizz.isPass = false;
	}*/

}

string GetFinalResultsText(bool Pass)
{

	if (Pass)
		return "Pass :-)";
	else
		return "Fail :-(";

}

void PrintQuizzResults(stQuizz Quizz)
{
	cout << "\n";
	cout << "____________________________________\n\n";
	cout << " Final Results is " << GetFinalResultsText(Quizz.isPass);
	cout << "\n____________________________________\n\n";

	cout << "Number of Questions: " << Quizz.NumberOfQuestion << endl;
	cout << "Questions Level    : " << GetQuestionLevelText(Quizz.QuestionsLevel) << endl;
	cout << "Operation Type     : " << GetOpTypeSymbol(Quizz.OpType) << endl;
	cout << "Number of Right Answer: " << Quizz.NumberOfRightAnswer << endl;
	cout << "Number of Wrong Answer: " << Quizz.NumberOfWrongAnswer << endl;
	cout << "____________________________________\n";

	SetScreenColor(Quizz.isPass);

}

void PlayMathGame()
{
	stQuizz Quizz;
	Quizz.NumberOfQuestion = ReadHowManyQuestions();
	Quizz.QuestionsLevel = ReadQuestionsLevel();
	Quizz.OpType = ReadOpType();

	GenerateQuizzQuestions(Quizz);
	AskAndCorrectQuestionListAnswer(Quizz);
	PrintQuizzResults(Quizz);

}

void ResetScreen()
{

	system("cls");
	system("color 0F");

}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{

		ResetScreen();
		PlayMathGame();

		cout << endl << "Do you want to play again? Y/N? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	//Seeds the random number generator in C++, called only once
	srand((unsigned)time(NULL));

	StartGame();

	return 0;

}