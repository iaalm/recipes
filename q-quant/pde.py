"""
This script used to calculate the price of a barrier option using the Black-Scholes model.
Solved with Finite Difference Method (FDM) on Partial Differential Equation (PDE).
"""
import QuantLib as ql
import matplotlib.pyplot as plt
import yfinance as yf
import numpy as np

# 获取英伟达（NVIDIA）的股票价格（2024/11/11 到 2025/11/11）
start_date = "2024-11-11"
end_date = "2025-11-11"
nvda_data = yf.download("NVDA", start=start_date, end=end_date, auto_adjust=True)

# 计算基于收盘价的历史波动率
close_prices = nvda_data[('Close', "NVDA")].values
# 计算对数收益率
log_returns = np.diff(np.log(close_prices))
# 计算年化波动率（假设252个交易日）
volatility = np.std(log_returns) * np.sqrt(252)

spot_price = nvda_data.iloc[0][('Close', "NVDA")]
strike_price = spot_price
barrier = strike_price * 1.45
print(f"Strike Price: {strike_price}, Barrier: {barrier}")
print(f"Calculated Annualized Volatility: {volatility*100:.2f}%")

# 定义市场参数
risk_free_rate = 0.05
barrier_payoff = 0.07
exercise_date = ql.Date(11, 12, 2025)

# 定义 QuantLib 对象
spot = ql.SimpleQuote(spot_price)
q_rate = ql.YieldTermStructureHandle(ql.FlatForward(0, ql.NullCalendar(), 0.0, ql.Actual365Fixed()))
r_rate = ql.YieldTermStructureHandle(ql.FlatForward(0, ql.NullCalendar(), risk_free_rate, ql.Actual365Fixed()))
vol = ql.BlackVolTermStructureHandle(ql.BlackConstantVol(0, ql.NullCalendar(), volatility, ql.Actual365Fixed()))

# Black-Scholes 模型
process = ql.BlackScholesMertonProcess(ql.QuoteHandle(spot), q_rate, r_rate, vol)

# 构造障碍期权
payoff = ql.PlainVanillaPayoff(ql.Option.Call, strike_price)
exercise = ql.EuropeanExercise(exercise_date)
option = ql.BarrierOption(ql.Barrier.UpOut, barrier, barrier_payoff, payoff, exercise)

# 设置有限差分引擎
engine = ql.FdBlackScholesBarrierEngine(process, 100, 200, 0)
option.setPricingEngine(engine)

prices = []
npvs = []
deltas = []
last_price = strike_price
last_delta = 0
simulated_npv = 1.0
simulated_npvs = []
for idx, data in nvda_data.iterrows():
    ql.Settings.instance().evaluationDate = ql.Date(data.name.day, data.name.month, data.name.year)
    price = data[('Close', "NVDA")]
    spot.setValue(price)
    prices.append(price)
    npv = option.NPV()
    npvs.append(npv / strike_price * 100)
    delta = option.delta()
    deltas.append(delta)

    pnl = (price / last_price - 1) * last_delta 
    simulated_npv *= (1 + pnl)
    simulated_npvs.append(simulated_npv)
    last_price = price
    last_delta = delta

plt.subplot(4, 1, 1)
plt.grid()
plt.title(f"Price underlying asset (Strike Price: {strike_price:.1f}, Barrier: {barrier:.1f})")
plt.plot(prices, label="Price")
plt.subplot(4, 1, 2)
plt.grid()
plt.title(f"Price of Barrier Option (% related to strike price) under Annualized Volatility: {volatility*100:.1f}%")
plt.plot(npvs, label="NPV")
plt.subplot(4, 1, 3)
plt.grid()
plt.title("Delta Curve of Barrier Option")
plt.plot(deltas, label="Delta")
plt.subplot(4, 1, 4)
plt.grid()
plt.title("Simulated NPV")
plt.plot(simulated_npvs, label="Simulated NPV")
plt.show()
