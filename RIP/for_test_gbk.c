#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
// #include <stdbool.h>
// #include <time.h>

// 定义详细的学生数据结构体
struct student_list
{
	// 定义学号
	unsigned int id;
	// 定义姓名
	char name[15];
};

// 清空输入区缓存
void clear_input_buffer()
{
	// 定义一个暂时存储读取字符缓冲区的int整型变量，因为char可能不够用
	int input_char = 0;
	/*反复读取直到读取到换行符或者文件的结尾
	如果读到文件结尾就直接跳出循环
	每次调用getchar会自动清除一个缓冲区的字符
	不过scanf依然不能解决中文输入的问题
	TMD为啥会有傻福往输入数字的地方输入中文啊？！*/
	while ((input_char = getchar()) != '\n')
	{
		// 如果读到文件结尾就跳出循环
		if (input_char == EOF)
		{
			break;
		}
	}
}

// 交换浮点数函数
void swap_float(float *a, float *b)
{
	float temp = *a;
	*a = *b;
	*b = temp;
}

// 冒泡排序,输入来自调用的函数给的变量
void bubble_sort(int students, float orderly_scores[])
{
	// 给循环用的局部变量
	int i = 0, j = 0;
	// 临时变量用来交换位置
	float temp = 0;
	// 有多少学生循环多少次
	for (i = 0; i < students - 1; i++) /*大循环*/
	{
		// 比较的是两个数，所以j+1不能超过数组的最大索引
		for (j = 0; j < students - i - 1; j++)
		{
			// 判断前后两数据大小
			if (orderly_scores[j] > orderly_scores[j + 1]) /*小循环*/
			{
				// 如果后者比前者大就交换位置
				temp = orderly_scores[j];
				orderly_scores[j] = orderly_scores[j + 1];
				orderly_scores[j + 1] = temp;
			}
		}
	}
}

// 快速排序分区函数
// 所有小于基准的都会被放到基准的左边
int partition(float arr[], int low, int high)
{
	// 默认最后一个为基准
	float pivot = arr[high];
	// 用来索引交换小于等于基准的值
	int i = low - 1;
	for (int j = low; j < high; j++)
	{
		if (arr[j] <= pivot)
		{
			i++;
			swap_float(&arr[i], &arr[j]);
		}
	}
	swap_float(&arr[++i],&arr[high]);
	return i;
}
// 快速排序主函数
// 变量low和high分别为分区最低位和最高位的索引
void q_sort_float(float arr[], int low, int high)
{
	if (low < high)
	{
		// 分区
		int pi = partition(arr, low, high);
		// 排序左边
		q_sort_float(arr, low, pi - 1);
		// 排序右边
		q_sort_float(arr, pi + 1, high);
	}
}

/*计算中位数（需要已经排序）
第二个参数是定义一个单精度浮点数组来接受参数*/
float calculate_median(int students, const float scores[])
{
	// 定义一个局部变量来储存计算后的中位数
	float median;
	// 如果学生人数是奇数，否则是偶数
	if (students % 2 == 1)
	{
		/*如果学生人数是奇数就给中位数赋值已排序数组中间的那个
		这里直接除于2是因为数组的索引从零开始
		C语言刚好索引商高一位，变成中位数的索引*/
		median = scores[students / 2];
	}
	else
	{
		/*如果学生人数是偶数，就要取中间两个的平均值
		这里直接除于2是因为数组的索引从零开始
		C语言刚好索引商高一位，变成中位数的索引*/
		median = ((scores[students / 2 - 1]) + scores[students / 2]) / 2;
	}
	// 最后返回median的值（float单精度浮点）
	return median;
}

// 查找众数的函数，传递了5个参数，其中返回的众数数组
// mode_count记录了众数个数，mode_max记录出现次数
// 学生默数，分数数组，中位数数组，返回众数数，返回最大众数次数
void find_mode(int students, float orderly_scores[], float modes[], int *mode_count_ptr, int *mode_max_ptr)
{
	// 定义当前众数，默认数组第一个
	float current_score = orderly_scores[0];
	// 定义当前众数计数，默认为1
	int current_count = 1;
	// 定义当前最大众数计数，认为1
	// 其实就是众数出现的次数
	int max_count = 1;
	// 定义当前众数个数，众数数组变动时候更新
	// 既是众数个数计数，也是数组的索引，有新众数写进去会自动改变索引
	// 其实就是有多少个众数
	int mode_count = 0;
	// 众数数组默认第一个是众数
	modes[mode_count++] = current_score;
	// 大循环，每个循环都有一个新的变量i被定义
	// 索引直接从数组第二个开始，第一个已经默认
	for (int i = 1; i < students; i++)
	// 注意：i++只会在一次大循环结束后才执行
	{
		// 比较数组中下一位和当前位的浮点数是否相等
		if (fabs(orderly_scores[i] /*下一位*/ - orderly_scores[i - 1] /*当前位*/) < 0.01)
		{
			// 相等就把当前计数增加
			current_count++;
		}
		else
		{
			// 如果不相等就开始统计下一个数
			// 注意：数组已经排序过了，如果遇到不相等的，接下来都不会再遇到相等的
			current_score = orderly_scores[i];
			// 重置当前众数计数
			current_count = 1;
		}
		// 存入或者覆写众数
		// 如果当前计数比最大计数更大
		if (current_count > max_count)
		{
			// 直接覆写
			// 先修改众数计数
			max_count = current_count;
			// 重置众数计数
			mode_count = 0;
			// 直接写入数组第一位，然后更新众数个数计数
			modes[mode_count++] = current_score;
		}
		// 如果两个众数计数一样大
		else if (current_count == max_count)
		{
			// 先检查众数数组里面有没有记录这个数
			// 其实我觉得这段判断没有必要
			// 定义一个整型变量来记录是否在数组中已经存在
			int exists = 0;
			// 用循环来判断，重复次数为众数个数
			for (int j = 0; j < mode_count; j++)
			{
				if (modes[j] == current_score)
				{
					exists = 1;
					break;
				}
			}
			// 如果不存在，就写入数组，并增加众数个数计数
			if (!exists)
			{
				modes[mode_count++] = current_score;
			}
		}
	}
	// 数组已经修改过了，这里返回计算结果
	*mode_count_ptr = mode_count;
	*mode_max_ptr = max_count;
}

// 共用一个循环来算总分，最高分，最低分
void for_to_calc(int students, float scores[], float *average_ptr, float *max_score_ptr, float *min_score_ptr, int *max_score_from_ptr, int *min_score_from_ptr)
{
	float average = 0;
	float max_score = scores[0];
	float min_score = scores[0];
	// 局部定义最高分来自谁的索引
	int max_score_from = 0;
	// 局部定义最低分来自谁的索引
	int min_score_from = 0;
	for (int i = 0; i < students; i++)
	{
		// 平均分先算全部加起来总分
		average += scores[i];
		// 算最高分
		if (scores[i] > max_score)
		{
			max_score = scores[i];
			max_score_from = i;
		}
		// 算最低分
		if (scores[i] < min_score)
		{
			min_score = scores[i];
			min_score_from = i;
		}
	}
	// 然后算平均分
	average = average / students;
	// 返回结果
	*average_ptr = average;
	*max_score_ptr = max_score;
	*min_score_ptr = min_score;
	*max_score_from_ptr = max_score_from;
	*min_score_from_ptr = min_score_from;
}
// 主函数
int main()
{
	// system("chcp 65001");
	system("chcp 936");
	// 别问我为啥学生数量用单精度浮点存
	float students_input = 0;
	int students = 0;
	printf("如果学生人数太大，会被调整为小于255的值，但通常小于255");
	printf("\n输入学生人数：\t");
	scanf(" %f", &students_input);
	clear_input_buffer();
	int i = 0;
	/* 给学生人数取绝对值，别问为什么
	这代码不是防bug的，是防傻逼的*/
	students_input = fabs(students_input);
	// 把小数的学生数量部分给忽略掉
	students = (int)students_input;
	students = students & 0x000000FF;
	printf("确认学生人数：\t%d\n", students);
	/* 定义一个记录学生分数的单精度浮点数数组*/
	float scores[students];
	// 让用户决定是否启用快速排序
	char enable_q_sort_float = '0';
	printf("\n是否启用快速排序？(y/n)\t");
	scanf(" %c", &enable_q_sort_float);
	clear_input_buffer();
	// 让用户决定是否用更详细的学生列表
	// 前面goto我尽量没用
	char enable_detailed_student_list = '0';
	printf("\n是否用更详细的学生列表？(y/n)\t");
	scanf(" %c", &enable_detailed_student_list);
	clear_input_buffer();
	// 让用户决定是否计算众数
	char if_mode = '0';
	printf("是否计算众数？(y/n)\t");
	scanf(" %c", &if_mode);
	clear_input_buffer();
	// 傻逼C语言逼我必须提前定义后面都不一定要用到的变量
	char if_auto_id = '0';
	// 傻逼C语言逼我必须提前定义后面都不一定要用到的结构体
	// 先定义个空指针
	struct student_list *class = NULL;
	/* 是否启用更详细的学生列表有两套方案，加上原来的有三套
	其中启用更详细的学生列表的两方案有共用部分
	忍无可忍啦，goto启动！！ */
	if (enable_detailed_student_list != 'y')
	{
		// 为啥这VS Code的C语言跳转这么乐色啊，目的地一点都不明显
		// 不过还有个F12的快捷键，还行
		goto DISABLE_DETAILED_LIST;
	}

	printf("\n是否自动写入学生学号？(y/n)\t");
	scanf(" %c", &if_auto_id);
	clear_input_buffer();
	// 傻逼C语言逼我必须提前定义后面都不一定要用到的结构体
	// 这里才真正分配内存
	class = malloc(students * sizeof(struct student_list));
	if (class == NULL)
	{
		// 分配内存失败直接退出
		printf("内存分配失败！\n");
		printf("程序退出……\n");
		// 都到这里了还不能用goto，气笑了，傻逼C语言就是不给跳过变量的定义和声明
		// 又是怀念汇编JMP的一次，不过汇编搞一堆标号命名也麻烦
		return 1;
	}
	printf("\n");
	// 通过for循环让用户输入每个学生的名字，如果有学号就顺带
	if (if_auto_id == 'y')
	{
		for (i = 0; i < students; i++)
		{
			class[i].id = i + 1;
		}
		for (i = 0; i < students; i++)
		{
			printf("输入学生%d的名字：\t", i + 1);
			// 这里的scanf没问题，但是不知道为啥VS Code爆红
			scanf(" %14s[^\n]", &class[i].name);
			// 每次输入完清空输入区缓存，防止某些傻福写特别长让程序崩溃或者让scanf错误赋值
			clear_input_buffer();
			printf("输入学生%d的分数：\t", i + 1);
			scanf(" %f", &scores[i]);
			// 每次输入完清空输入区缓存，防止某些傻福写特别长让程序崩溃或者让scanf错误赋值
			clear_input_buffer();
			printf("\n");
		}
	}
	else
	{
		for (i = 0; i < students; i++)
		{
			printf("输入学生%d的学号：", i + 1);
			scanf(" %u", &class[i].id);
			// 每次输入完清空输入区缓存，防止某些傻福写特别长让程序崩溃或者让scanf错误赋值
			clear_input_buffer();
			// 这里的scanf没问题，但是不知道为啥VS Code爆红
			printf("输入学生%d的名字：", i + 1);
			scanf(" %14s[^\n]", &class[i].name);
			// 每次输入完清空输入区缓存，防止某些傻福写特别长让程序崩溃或者让scanf错误赋值
			clear_input_buffer();
			printf("输入学生%d的分数：", i + 1);
			scanf(" %f", &scores[i]);
			// 每次输入完清空输入区缓存，防止某些傻福写特别长让程序崩溃或者让scanf错误赋值
			clear_input_buffer();
			printf("\n");
		}
	}
	// 循环打印确认每个学生信息
	printf("学生信息确认：\n\n");
	for (i = 0; i < students; i++)
	{
		printf("确认学生%d学号：\t%u\n", i + 1, class[i].id);
		printf("确认学生%d名字：\t%s\n", i + 1, class[i].name);
		printf("确认学生%d分数：\t%.2f\n\n", i + 1, scores[i]);
	}
	goto ENABLE_DETAILED_LIST_NEXT;
	// 标号好评，真的好用
DISABLE_DETAILED_LIST:
	printf("\n");
	// 通过for循环让用户输入每个学生的分数
	for (i = 0; i < students; i++)
	{
		printf("输入学生%d的分数：", i + 1);
		scanf(" %f", &scores[i]);
		// 每次输入完清空输入区缓存，防止某些傻福写特别长让程序崩溃或者让scanf错误赋值
		clear_input_buffer();
	}
	// 循环打印确认每个学生分数
	for (i = 0; i < students; i++)
	{
		printf("确认学生%d分数：%.2f\n", i + 1, scores[i]);
	}
ENABLE_DETAILED_LIST_NEXT:
	// 定义平均分，然后计算
	float average = 0;
	// 定义最高分，然后计算
	float max_score = scores[0];
	// 定义最低分，然后计算
	float min_score = scores[0];
	// 直接定义一个排序后数组，方便调用
	float orderly_scores[students];
	// 拷贝数组，排序用，防止打乱原来的数组
	memcpy(orderly_scores, scores, students * sizeof(float));
	// 调用排序
	if (enable_q_sort_float != 'y')
	{
		goto DISABLE_Q_SORT_FLOAT;
	}
	// 快速排序
	q_sort_float(orderly_scores, 0, students - 1);
	// 跳转继续
	goto ENABLE_Q_SORT_FLOAT_NEXT;
// 不使用快速排序
DISABLE_Q_SORT_FLOAT:
	// 泡泡排序
	bubble_sort(students, orderly_scores);
// 继续
ENABLE_Q_SORT_FLOAT_NEXT:
	if (!(enable_detailed_student_list == 'y'))
	{
		goto NO_MAX_SCORE_FROM;
	}
	// 定义最高分来自谁的索引
	int max_score_from = 0;
	// 定义最低分来自谁的索引
	int min_score_from = 0;
	// 调用计算分数函数
	for_to_calc(students, scores, &average, &max_score, &min_score, &max_score_from, &min_score_from);
	goto MAX_SCORE_FROM_NEXT;
NO_MAX_SCORE_FROM:
	// 调用计算分数函数
	for_to_calc(students, scores, &average, &max_score, &min_score, &max_score_from, &min_score_from);
	goto NO_MAX_SCORE_FROM_NEXT;
MAX_SCORE_FROM_NEXT:
NO_MAX_SCORE_FROM_NEXT:
	/*计算中位数，传递学生数和关于学生分数的数组
	直接定义了一个局部float单精度浮点变量来储存中位数并用中位数函数赋值*/
	float median = calculate_median(students, orderly_scores);

	// 打印输出
	printf("\n计算结果：\n\n");
	printf("平均分：\t%.2f\n", average);
	printf("最高分：\t%.2f\n", max_score);
	printf("最低分：\t%.2f\n", min_score);
	printf("中位数：\t%.2f\n", median);
	// 决定是否输出最高分来自谁
	if (!(enable_detailed_student_list == 'y'))
	{
		// 没有启用详细就跳过最高分所有者打印
		goto NO_PRINT_MAX_SCORE_FROM;
	}
	printf("\n最高分%.2f分，来自%s\n", scores[max_score_from], class[max_score_from].name);
NO_PRINT_MAX_SCORE_FROM:
	// 决定是否计算众数
	if (if_mode == 'y')
	// 这里禁止用goto，因为里面有定义式
	{
		// 定义一个所谓众数数组
		float modes[students];
		// 定义所谓众数计数
		int mode_count = 0;
		// 定义所谓众数出现次数
		int mode_max = 0;
		find_mode(students, orderly_scores, modes, &mode_count, &mode_max);
		// 调试，输出众数
		// 有多少个众数就输出多少个，众数个数就是mode_count的值
		printf("\n众数计算结果：\n\n");
		// 判断有没有众数，取决于众数出现次数
		if (mode_max > 1)
		{
			printf("找到%d个众数\n", mode_count);
			printf("出现次数均为%d次\n\n", mode_max);
			for (i = 0; i < mode_count; i++)
			{
				printf("众数第\t%d个：\t%.2f\n", i + 1, modes[i]);
			}
		}
		else
		{
			printf("没有找到众数\n");
		}
	}
	// 结尾标号，实际上C语言不允许前面大多数地方跳转到这里
ENDS:
	printf("\n");
	if (class != NULL)
	{
		free(class);
		class = NULL;
	}
	// 调用windows暂停
	system("pause");
	return 0;
}