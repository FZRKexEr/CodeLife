#!/usr/bin/env python3
# from typing import *



# def solve(testcases: int, a: List[int], b: List[int], c: List[int], d: List[int]) -> Any:
def solve(testcases, a, b, c, d):
    pass  # TODO: edit here

# generated by oj-template v4.8.1 (https://github.com/online-judge-tools/template-generator)
def main():
    testcases = int(input())
    a = [None for _ in range(testcases)]
    b = [None for _ in range(testcases)]
    c = [None for _ in range(testcases)]
    d = [None for _ in range(testcases)]
    for i in range(testcases):
        a[i] = int(input())
        assert input() == ''
        b[i] = int(input())
        assert input() == ''
        c[i] = int(input())
        assert input() == ''
        d[i] = int(input())
    ans = solve(testcases, a, b, c, d)
    print(ans)  # TODO: edit here

if __name__ == '__main__':
    main()