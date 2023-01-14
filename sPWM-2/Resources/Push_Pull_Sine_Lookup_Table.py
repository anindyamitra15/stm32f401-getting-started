import math

amplitude = int(input("Enter the peak amplitude duty cycle (default 900): ") or "900")
data_points = int(
    input("Enter the number of data points per half cycle(default 200): ") or "200"
)

angles = list(map(lambda x: math.pi * x / (data_points), [m for m in range(0, data_points)]))

amplitudes = list(map(lambda x: round(math.sin(x) * amplitude), angles))

half_lut_len = len(amplitudes)

sPWM_CH1_LUT = amplitudes + [0] * half_lut_len

sPWM_CH2_LUT = [0] * half_lut_len + amplitudes

print(f"\n#define LUT_LEN {2*half_lut_len}\n")

print(
    "uint16_t sPWM_CH1_LUT[LUT_LEN] = {"
    + (str(sPWM_CH1_LUT)[1:-1])
    + "};"
)

print()

print(
    "uint16_t sPWM_CH2_LUT[LUT_LEN] = {"
    + (str(sPWM_CH2_LUT)[1:-1])
    + "};"
)
