"""
This script used to calculate the price of a barrier option using the Black-Scholes model.
Solved with Finite Difference Method (FDM) on Partial Differential Equation (PDE).
"""
from QuantLib import *
import matplotlib.pyplot as plt

# 定义市场参数
spot_price = 100.0
strike_price = 100.0
volatility = 0.4
risk_free_rate = 0.05
maturity = 0.01  # change to 0.01 is interesting
barrier = 145.0
barrier_payoff = 0.07

# 定义 QuantLib 对象
spot = SimpleQuote(spot_price)
q_rate = YieldTermStructureHandle(FlatForward(0, NullCalendar(), 0.0, Actual365Fixed()))
r_rate = YieldTermStructureHandle(FlatForward(0, NullCalendar(), risk_free_rate, Actual365Fixed()))
vol = BlackVolTermStructureHandle(BlackConstantVol(0, NullCalendar(), volatility, Actual365Fixed()))

# Black-Scholes 模型
process = BlackScholesMertonProcess(QuoteHandle(spot), q_rate, r_rate, vol)

# 构造障碍期权
payoff = PlainVanillaPayoff(Option.Call, strike_price)
exercise = EuropeanExercise(Date.todaysDate() + int(365 * maturity))
option = BarrierOption(Barrier.UpOut, barrier, barrier_payoff, payoff, exercise)

# 设置有限差分引擎
engine = FdBlackScholesBarrierEngine(process, 100, 200, 0)
option.setPricingEngine(engine)

# 计算期权价格
price = option.NPV()
print("Option Price:", option.NPV())
print("Option Delta:", option.delta())
print("Option Theta:", option.theta())
print("Option Gamma:", option.gamma())


spot_prices = [80 + 3 * i for i in range(22)]
deltas = []
prices = []
thetas = []
gammas = []

for s in spot_prices:
    spot.setValue(s)
    delta = option.delta()
    deltas.append(delta)
    price = option.NPV()
    prices.append(price)
    theta = option.theta()
    thetas.append(theta)
    gamma = option.gamma()
    gammas.append(gamma)


plt.subplot(4, 1, 1)
plt.plot(spot_prices, deltas, label="Delta Curve")
plt.legend()
plt.grid()
plt.subplot(4, 1, 2)
plt.plot(spot_prices, prices, label="Price Curve")
plt.legend()
plt.grid()
plt.subplot(4, 1, 3)
plt.plot(spot_prices, thetas, label="Theta Curve")
plt.legend()
plt.grid()
plt.subplot(4, 1, 4)
plt.plot(spot_prices, gammas, label="Gamma Curve")
plt.legend()
plt.grid()
plt.show()
