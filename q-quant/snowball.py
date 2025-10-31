import QuantLib as ql
import numpy as np

# 参数定义
S0 = 100  # 标的资产初始价格
K = 100  # 敲出价格
Kn = 80  # 敲入价格
r = 0.03  # 无风险利率
sigma = 0.2  # 波动率
T = 1.0  # 到期期限（1年）
dS = 0.01  # 标的价格微调步长
steps = 252  # 时间步数
simulations = 10000  # 模拟路径数量

# 时间和收益率曲面设置
calendar = ql.NullCalendar()
day_count = ql.Actual365Fixed()
today = ql.Date(11, 12, 2024)
ql.Settings.instance().evaluationDate = today
maturity_date = calendar.advance(today, int(T * 365), ql.Days)

spot_quote = ql.SimpleQuote(S0)
spot_handle = ql.QuoteHandle(spot_quote)
rate_handle = ql.YieldTermStructureHandle(ql.FlatForward(today, r, day_count))
vol_handle = ql.BlackVolTermStructureHandle(
    ql.BlackConstantVol(today, calendar, sigma, day_count)
)

# 构建标的资产价格过程
process = ql.BlackScholesProcess(spot_handle, rate_handle, vol_handle)

# 模拟器设置
rng = ql.GaussianRandomSequenceGenerator(
    ql.UniformRandomSequenceGenerator(steps, ql.UniformRandomGenerator())
)
seq = ql.GaussianPathGenerator(process, T, steps, rng, False)

# 模拟路径
def generate_paths(seq, n):
    paths = []
    for _ in range(n):
        sample_path = seq.next()
        path = sample_path.value()
        values = np.array([path[i] for i in range(len(path))])
        paths.append(values)
    return np.array(paths)

# 雪球产品定价逻辑
def calculate_snowball_value(paths, K, Kn, T):
    payoffs = []
    for path in paths:
        knocked_out = (path >= K).any()
        knocked_in = (path <= Kn).any()

        if knocked_out:
            payoffs.append(0.1 * S0)  # 假设敲出收益为10%
        elif knocked_in:
            payoffs.append(path[-1] - S0)  # 敲入收益
        else:
            payoffs.append(0)  # 未敲入或敲出
    return np.mean(payoffs) * np.exp(-r * T)  # 折现

# 计算初始价值和Delta
paths = generate_paths(seq, simulations)
initial_value = calculate_snowball_value(paths, K, Kn, T)

# 调整标的价格计算Delta
spot_quote.setValue(S0 + dS)  # 更新标的价格
paths_up = generate_paths(seq, simulations)
value_up = calculate_snowball_value(paths_up, K, Kn, T)

spot_quote.setValue(S0 - dS)  # 更新标的价格
paths_down = generate_paths(seq, simulations)
value_down = calculate_snowball_value(paths_down, K, Kn, T)

delta = (value_up - value_down) / (2 * dS)

print(f"雪球产品的初始价值: {initial_value:.4f}")
print(f"雪球产品的Delta: {delta:.4f}")
