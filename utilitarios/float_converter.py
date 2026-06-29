import struct
import math

def float_to_binary(number):

    scaled_number = int(round(number * (2**8)))

    binary_16bit = bin(scaled_number & 0xFFFF)[2:].zfill(16)

    integer_part = binary_16bit[:8]
    fractional_part = binary_16bit[8:]

    return f"{integer_part}.{fractional_part}"


def float_to_hexadecimal(number):
    bits = struct.unpack('>I', struct.pack('>f', number))[0]
    return f'0x{bits:08x}'



float_number = 62.625

hex_number = float_to_hexadecimal(float_number)
binary_number = float_to_binary(float_number)


print("numero em binario:")
print(f'{binary_number}\n')
print("numero em hexadecimal:")
print(hex_number)