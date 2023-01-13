import math

amplitude = int(input('Enter the amplitude (default 900): ') or "900")
data_points =  int(input('Enter the number of data points (default 200): ') or "200")
    
angles = list(
        map(
            lambda x: math.pi*x/(200),
            [m for m in range(0, data_points)]
        )
    )
LUT = list(
        map(
            lambda x: round(math.sin(x)*amplitude), 
            angles
        )
    )

print(f"\n#define LUT_LEN {len(LUT)}\n")
print("uint16_t sPWM_LUT[LUT_LEN] = {" + (str(LUT)[1:-1]) + "};")
