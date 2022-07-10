#
#  作业1.py
#  2022-06-26 00:35
#
#  Created by liznb
# 

class StudentSystem(object):
    def __init__(self):
        self.student = []
    
    def print_std(self, std):
        print("--------------------")
        print("name:", std["name"]) 
        print("number:", std["number"])
        print("gender:", std["gender"])
        print("date:", std["date"])
        print("from:", std["from"])
        print("--------------------")

    
    def print(self):
        for std in self.student:
            self.print_std(std) 

    def find(self, name):
        for std in self.student:
            if std["name"] == name:
                return std
        return None

    def add(self):
        std = {}
        std["name"] = input("请输入姓名:") 
        std["number"] = input("请输入学号:")
        std["gender"] = input("请输入性别:")
        std["date"] = input("请输入生日:")
        std["from"] = input("请输入籍贯:")
        return std

    def erase(self, name):
        for i in range(len(self.student)):
            if self.student[i]["name"] == name:
                self.student.pop(i)
                return


if __name__ == "__main__":
    user = "root"
    passwd = "1234"
    a = input("请输入账号:")
    b = input("请输入密码:")
    if user == a and passwd == b:
        database = StudentSystem()
        while True:
            print("------学生信息管理系统-------")
            print("请选择功能")
            print("1. 浏览学生信息") 
            print("2. 查询学生信息") 
            print("3. 更改学生信息") 
            print("4. 删除学生信息") 
            o = int(input())
            if o == 1:
                database.print()
            elif o == 2:
                name = input("请输入学生姓名:")
                std = database.find(name)     
                if std == None:
                    print("查无此人")
                else:
                    database.print_std(std)
            elif o == 3:
                name = input("请输入学生姓名:")
                std = database.find(name) 
                if std == None:
                    print("现在添加", name, "的信息")
                    std = database.add()
                    database.student.append(std)
                else:
                    print("请重新输入", name, "修改后的信息")
                    std = database.add()
                    database.erase(name)
                    database.student.append(std)
            elif o == 4:
                name = input("请输入学生姓名")
                database.erase(name)
                print("已删除", name, "的信息")
    else:
        print("账号或者密码错误, 再见")
