# 基于前移法的链表查找

## 题目背景

2023, ds, half-term-exam, T2

## 题目描述

链表结构存在一个严重不足，就是需要顺序$\color{red}查找$才能找到所需要的元素，查找性能低，下面为一个改进链表查找效率的方法。
链表构造规则如下：

1. 初始时链表为空；
2. 若元素不在链表中，将其加到链表尾；
3. 若元素在链表中，则将该元素移到链表头（若元素已在链表头则不移动）。

编写程序，对输入的一组整数，依次在上述规则构建的链表中查找每个整数。

## 输入格式

从标准输入读入两行
第一行，一个整数n表示要查找的整数的个数(n>0)
第二行，n个数用空格间隔开，表示要查找的整数

## 输出格式

前五行，输出最终链表前五个整数及其出现次数，中间用空格间隔开
当整数种类不足五时，按上述要求输出全部整数
最后一行，输出过程中总的比较次数

## 样例

### Group1

#### stdin

15
-200 120 85 97 2900 85 696 -120 85 120 85 120 85 97 120

#### stdout

120 4
97 2
85 5
-200 1
2900 1
41

## 说明/提示

样例的运行日志如下：
check "-200" 0 times&emsp;&emsp;list is: -200(1)
check &ensp;"120" 1 times&emsp;&emsp;list is: -200(1)$\rightarrow$120(1)
check &ensp;&ensp;"85" 2 times&emsp;&emsp;list is: -200(1)$\rightarrow$120(1)$\rightarrow$85(1)
check &ensp;&ensp;"97" 3 times&emsp;&emsp;list is: -200(1)$\rightarrow$120(1)$\rightarrow$85(1)$\rightarrow$97(1)
check "2900" 4 times&emsp;&emsp;list is: -200(1)$\rightarrow$120(1)$\rightarrow$85(1)$\rightarrow$97(1)$\rightarrow$2900(1)
check &ensp;&ensp;"85" 3 times&emsp;&emsp;list is: 85(2)$\rightarrow$-200(1)$\rightarrow$120(1)$\rightarrow$97(1)$\rightarrow$2900(1)
check &ensp;"696" 5 times&emsp;&emsp;list is: 85(2)$\rightarrow$-200(1)$\rightarrow$120(1)$\rightarrow$97(1)$\rightarrow$2900(1)$\rightarrow$696(1)
check "-120" 6 times&emsp;&emsp;list is: 85(2)$\rightarrow$-200(1)$\rightarrow$120(1)$\rightarrow$97(1)$\rightarrow$2900(1)$\rightarrow$696(1)$\rightarrow$-120(1)
check &ensp;&ensp;"85" 1 times&emsp;&emsp;list is: 85(3)$\rightarrow$-200(1)$\rightarrow$120(1)$\rightarrow$97(1)$\rightarrow$2900(1)$\rightarrow$696(1)$\rightarrow$-120(1)
check &ensp;"120" 3 times&emsp;&emsp;list is: 120(2)$\rightarrow$85(3)$\rightarrow$-200(1)$\rightarrow$97(1)$\rightarrow$2900(1)$\rightarrow$696(1)$\rightarrow$-120(1)
check &ensp;&ensp;"85" 2 times&emsp;&emsp;list is: 85(4)$\rightarrow$120(2)$\rightarrow$-200(1)$\rightarrow$97(1)$\rightarrow$2900(1)$\rightarrow$696(1)$\rightarrow$-120(1)
check &ensp;"120" 2 times&emsp;&emsp;list is: 120(3)$\rightarrow$85(4)$\rightarrow$-200(1)$\rightarrow$97(1)$\rightarrow$2900(1)$\rightarrow$696(1)$\rightarrow$-120(1)
check &ensp;&ensp;"85" 2 times&emsp;&emsp;list is: 85(5)$\rightarrow$120(3)$\rightarrow$-200(1)$\rightarrow$97(1)$\rightarrow$2900(1)$\rightarrow$696(1)$\rightarrow$-120(1)
check &ensp;&ensp;"97" 4 times&emsp;&emsp;list is: 97(2)$\rightarrow$85(5)$\rightarrow$120(3)$\rightarrow$-200(1)$\rightarrow$2900(1)$\rightarrow$696(1)$\rightarrow$-120(1)
check &ensp;"120" 3 times&emsp;&emsp;list is: 120(4)$\rightarrow$97(2)$\rightarrow$85(5)$\rightarrow$-200(1)$\rightarrow$2900(1)$\rightarrow$696(1)$\rightarrow$-120(1)

### 数据规模

保证要查找的数字在int范围内
