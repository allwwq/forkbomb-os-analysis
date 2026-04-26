import matplotlib.pyplot as plt
import numpy as np

with open("createprocess_bomb.log", 'r') as f:
    timestamps = np.array([int(line.strip()) for line in f if line.strip()])

timestamps_seconds = timestamps / 1e9

monotonic = np.zeros_like(timestamps_seconds)
monotonic[0] = timestamps_seconds[0]

for i in range(1, len(timestamps_seconds)):
    if timestamps_seconds[i] > monotonic[i-1]:
        monotonic[i] = timestamps_seconds[i]
    else:
        monotonic[i] = monotonic[i-1] + 0.000001 

time_from_start = monotonic - monotonic[0]
x = np.arange(len(time_from_start))

# График
plt.figure(figsize=(12, 7))
plt.plot(x, time_from_start, 'b-', linewidth=2)
plt.xlabel('Количество процессов')
plt.ylabel('Время с момента запуска (секунды)')
plt.grid(True, alpha=0.3)
plt.savefig('monotonic_graph.png', dpi=300)
plt.show()