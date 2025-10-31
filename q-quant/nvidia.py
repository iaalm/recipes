import QuantLib as ql
import numpy as np
import matplotlib.pyplot as plt

# 参数定义
spot_price = 100  # 初始标的价格
risk_free_rate = 0.03  # 无风险利率
volatility = 0.2  # 标的资产波动率
maturity = 2  # 到期时间
strike_low = 100
strike_high = 130
notional = 100

# QuantLib设置
calculation_date = ql.Date(11, 12, 2024)
ql.Settings.instance().evaluationDate = calculation_date
day_count = ql.Actual365Fixed()
calendar = ql.NullCalendar()

# 定义标的资产价格过程
spot_handle = ql.QuoteHandle(ql.SimpleQuote(spot_price))
rate_handle = ql.YieldTermStructureHandle(ql.FlatForward(calculation_date, risk_free_rate, day_count))
vol_handle = ql.BlackVolTermStructureHandle(ql.BlackConstantVol(calculation_date, calendar, volatility, day_count))
process = ql.BlackScholesProcess(spot_handle, rate_handle, vol_handle)

# 定义Monte Carlo引擎
timestep_per_year = 252
n_scenarios = 10000  # 模拟路径数量
rng = ql.GaussianRandomSequenceGenerator(ql.UniformRandomSequenceGenerator(timestep_per_year * maturity, ql.UniformRandomGenerator()))
seq = ql.GaussianPathGenerator(process, maturity, timestep_per_year, rng, False)

# 定义定价函数
def monte_carlo_price(spot_price):
    spot_handle.setValue(spot_price)
    paths = [seq.next()[0] for _ in range(n_scenarios)]  # 模拟路径
    payoffs = []

    for path in paths:
        final_price = path.back()
        if final_price > strike_high:
            payoff = notional * 1.1  # 支付110元
        elif strike_low <= final_price <= strike_high:
            payoff = final_price  # 同比例回报
        else:
            payoff = notional  # 返回本金
        payoffs.append(payoff)

    discounted_payoff = np.mean(payoffs) * np.exp(-risk_free_rate * maturity)  # 现值
    return discounted_payoff

# 计算Delta
spots = np.linspace(80, 150, 50)
prices = np.array([monte_carlo_price(s) for s in spots])
deltas = np.gradient(prices, spots)

# 绘制价格和Delta曲线
plt.figure(figsize=(12, 6))
plt.subplot(1, 2, 1)
plt.plot(spots, prices, label="Price")
plt.title("Price Curve of Structured Product")
plt.xlabel("Underlying Asset Price (S)")
plt.ylabel("Price")
plt.grid()

plt.subplot(1, 2, 2)
plt.plot(spots, deltas, label="Delta", color="orange")
plt.title("Delta Curve of Structured Product")
plt.xlabel("Underlying Asset Price (S)")
plt.ylabel("Delta")
plt.axhline(0, color='black', linestyle='--', linewidth=0.8)
plt.grid()

plt.tight_layout()
plt.show()
