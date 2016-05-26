// levenshteinDistance.cpp : Defines the entry point for the console application.
//

#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdint.h>
#include <string>

uint32_t levenshteinDistance(char* pSrc, uint32_t lenSrc, char* pDest, uint32_t lenDest);

uint32_t levenshteinDynamicProgramming(char* pSrc, uint32_t lenSrc, char* pDest, uint32_t lenDest);

uint32_t levenshteinTwoRows(char* pSrc, uint32_t lenSrc, char* pDest, uint32_t lenDest);

int _tmain(uint32_t argc, _TCHAR* argv[])
{

    while (1)
    {
        char sourceStr[100] = { 0 };
        char destStr[100] = { 0 };
        printf("please enter zhe Source world(exit to end):");
        scanf("%s", sourceStr);
        if (strcmp(sourceStr, "exit") == 0)
        {
            break;
        }

        printf("please enter zhe Dest world:");
        scanf("%s", destStr);

        uint32_t s_len = strlen(sourceStr);
        uint32_t t_len = strlen(destStr);

        char* s = sourceStr;
        char* t = destStr;

        uint32_t mindis = 0;
        mindis = levenshteinDistance(s, s_len, t, t_len);
        printf("ʹ�õݹ鷽��ʵ�ֵ�����˹̹�����㷨��������%3d\n\n", mindis);

        mindis = levenshteinDynamicProgramming(s, s_len, t, t_len);
        printf("ʹ���Ե����Ϸ�ʽ�Ķ�̬�滮ʵ�ֵ�����˹̹�����㷨��������%3d\n\n", mindis);

        mindis = levenshteinTwoRows(s, s_len, t, t_len);
        printf("ʹ�þ������е�����ʵ�ֵ�����˹̹�����㷨��������%3d\n", mindis);
    }
  

    system("pause");
	return 0;
}

template<typename T>
T Min(T x, T y, T z)
{
    if (x <= y && x <= z)
    {
        return x;
    }
    else if (y <= z)
    {
        return y;
    }
    else
    {
        return z;
    }
}

// �ݹ�ʵ��
uint32_t levenshteinDistance(char* pSrc, uint32_t lenSrc, char* pDest, uint32_t lenDest)
{
    if (lenSrc == 0)
    {
        return lenDest;
    }

    if (lenDest == 0)
    {
        return lenSrc;
    }

    uint32_t coust = pSrc[lenSrc - 1] == pDest[lenDest - 1] ? 0 : 1;

    return Min(levenshteinDistance(pSrc, lenSrc - 1, pDest, lenDest) + 1, 
               levenshteinDistance(pSrc, lenSrc, pDest, lenDest -1) + 1, 
               levenshteinDistance(pSrc, lenSrc - 1, pDest, lenDest -1) + coust);

}

// ����̬�滮ʵ��
uint32_t levenshteinDynamicProgramming(char* pSrc, uint32_t lenSrc, char* pDest, uint32_t lenDest)
{
    if (lenSrc == 0 || pSrc == NULL)
    {
        return lenDest;
    }

    if (lenDest == 0 || pDest == NULL)
    {
        return lenSrc;
    }

    uint32_t width = lenDest + 1;
    uint32_t hight = lenSrc + 1;

    uint32_t arraySize = width * hight * sizeof(uint32_t);
    uint32_t* pArray = (uint32_t *)malloc(arraySize);
    if (pArray == NULL)
    {
        return lenDest > lenSrc ? lenDest : lenSrc;
    }

    memset(pArray, 0, arraySize);

    // ��ʼ����һ�� �൱��Դ�ַ�������ɾ���õ����ַ�Ҫ�����Ĳ���
    for (uint32_t i = 0; i < hight; ++i)
    {
        pArray[i * width] = i;

    }

    // ��ʼ����һ�� �൱��Դ�ַ����ӿ����ε�Ŀ���ַ���Ҫ�����Ĳ���
    for (uint32_t i = 0; i < width; ++i)
    {
        pArray[i] = i;
    }

    for (uint32_t j = 0; j < lenDest; ++j)
    {
        for (uint32_t i = 0; i < lenSrc; ++i)
        {
            if (pSrc[i] == pDest[j])
            {
                pArray[(i + 1) * width + (j + 1)] = pArray[i * width + j];
            }
            else
            {
                pArray[(i + 1) *width + (j + 1)] = Min(pArray[i * width + j + 1], pArray[(i + 1) * width + j], pArray[i * width + j]) + 1;
            }
        }
    }

    // ��ӡ����
    printf("�������Ϊ��\r\n");
    for (uint32_t i = 0; i < hight; ++i)
    {
        for (uint32_t j = 0; j < width; ++j)
        {
            printf("%d ", pArray[i * width + j]);
        }
        printf("\r\n");
    }

    uint32_t result = pArray[width * hight - 1];

    free(pArray);

    return result;
}

// ˫����ģ�����ʵ��
uint32_t levenshteinTwoRows(char* pSrc, uint32_t lenSrc, char* pDest, uint32_t lenDest)
{
    if (lenSrc == 0 || pSrc == NULL)
    {
        return lenDest;
    }

    if (lenDest == 0 || pDest == NULL)
    {
        return lenSrc;
    }

    uint32_t width = lenDest + 1;
    uint32_t hight = lenSrc + 1;

    uint32_t arraySize = 2 * width * sizeof(uint32_t);
    uint32_t* pArray = (uint32_t *)malloc(arraySize);
    if (pArray == NULL)
    {
        return lenDest > lenSrc ? lenDest : lenSrc;
    }

    memset(pArray, 0, arraySize);

    // ���Դ�ַ����ӿ����ӵ�Ŀ���ַ���
    for (uint32_t i = 0; i < width; ++i)
    {
        pArray[i] = i;
    }

    printf("�������м����Ϊ:\r\n");
    for (uint32_t i = 0; i < width; ++i)
    {
        printf("%d ", pArray[i]);
    }
    printf("\r\n");

    for (uint32_t i = 1; i < hight; ++i)
    {
        pArray[width] = i;
        for (uint32_t j = 1; j < width; ++j)
        {
            if (pSrc[i - 1] == pDest[j - 1])
            {
                pArray[width + j] = pArray[j - 1];
            }
            else
            {
                pArray[width + j] = Min(pArray[j], pArray[width + j - 1], pArray[j - 1]) + 1;
            }
        }

        // �ѵ�2��������Ϊ��һ������
        for (uint32_t t = 0; t < width; ++t)
        {
            pArray[t] = pArray[width + t];
        }

        ////////////////////////////////////////////////////////
        for (uint32_t k = 0; k < width; ++k)
        {
            printf("%d ", pArray[k]);
        }
        printf("\r\n");
        ////////////////////////////////////////////////////////
    }


    uint32_t result = pArray[2 * width - 1];

    free(pArray);

    return result;
}

