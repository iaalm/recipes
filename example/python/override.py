class father:
    def fun(self):
        print("a")
    def caller(self):
        father.fun(self)
        self.fun()

class son(father):
    def fun(self):
        print("b")

if __name__ == "__main__":
    father().caller()
    son().caller()
