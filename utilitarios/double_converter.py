import struct
import math

def double_to_binary(number):

    bits = struct.unpack('>Q', struct.pack('>d', number))[0]

    binary_64bit = bin(bits)[2:].zfill(64)

    integer_part = binary_64bit[:32]
    fractional_part = binary_64bit[32:]

    return f"{integer_part}.{fractional_part}"


def double_to_hexadecimal(number):
    bits = struct.unpack('>Q', struct.pack('>d', number))[0]
    return f'0x{bits:016x}'


double_number = 37.25

hex_number = double_to_hexadecimal(double_number)
binary_number = double_to_binary(double_number)


print("numero em binario:")
print(f'{binary_number}\n')

print("numero em hexadecimal:")
print(hex_number)