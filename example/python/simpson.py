#/usr/bin/python3

#simpson积分算法，属于数值分析的范畴，计算f在a到b上的定积分，误差在e范围内

import math
def simpson(f, a, b, e):
    hf = (a + b) / 2
    res = S(f, a, hf) + S(f, hf, b)
    if abs(S(f, a, b) - res) < 15 * e:
        return res
    else:
        return simpson(f, a, hf, e / 2) + simpson(f, hf, b, e / 2)

def S(f, a, b):
    h = (b - a) / 2
    return h / 3 * (f(a) + 4 * f(a+h) + f(b))

if __name__ == '__main__':
    print(simpson(lambda x:x,0 ,1 ,0.1))
    print(simpson(lambda x:x**2,0 ,1 ,0.1))
    print(simpson(lambda x:math.sin(x),0 ,math.pi ,0.0000001))
    print(simpson(lambda x:math.cos(x),0 ,math.pi ,0.0000001))
