#
#  checker.py
#  2022-07-04 18:01
#
#  Created by liznb
#

import os
import difflib


# 不带后缀输入文件名, 必须是 cpp 文件

def main():
    sj = input("输入数据生成器文件名: ")
    std = input("输入标准程序文件名: ")
    sol = input("输入待测试程序文件名: ")
    num = int(input("输入测试数据组数: "))
    print("正在编译")
    os.system("g++-11 " + sj + ".cpp -o " + sj)
    os.system("g++-11 " + std + ".cpp -o " + std)
    os.system("g++-11 " + sol + ".cpp -o " + sol)
    print("编译结束")

    if os.path.exists("./test"):
        os.system("rm -rf ./test")

    os.mkdir("test")
    for i in range(1, num + 1):
        print("正在生成第", i, "组数据")
        os.system("./" + sj + " > " + "./test/" + str(i) + ".in")
        os.system("(cat ./test/" + str(i) + ".in | ./" + std + " ) > ./test/" + str(i) + ".out")

    for i in range(1, num + 1):
        print("第", i, "组数据: ", end = "")
        os.system("(cat ./test/" + str(i) + ".in | ./" + sol + " ) > ./out.txt")
        if os.environ.get("?") != 0:
            print("RE")

        os.system("diff -b -B out.txt ./test/" + str(i) + ".out > /dev/null 2>&1")
        if os.environ.get("?") != 0:
            print("WA")
        else:
            print("AC")

    return

if __name__ == "__main__":
    main()
