import struct

def float_to_binary(number):
    integer_part = int(number)
    fractional_part = number - integer_part

    integer_binary = bin(integer_part)[2:]

    fractional_binary = ""
    while fractional_part > 0:
        fractional_part *= 2
        bit = int(fractional_part)
        fractional_binary += str(bit)
        fractional_part -= bit

    return f"{integer_binary}.{fractional_binary}" if fractional_binary else integer_binary


def float_to_hexadecimal(number):
    bits = struct.unpack('>I', struct.pack('>f', number))[0]
    return f'0x{bits:08x}'



float_number = -4.5

hex_number = float_to_hexadecimal(float_number)
binary_number = float_to_binary(float_number)

print("numero em binario:")
print(f'{binary_number}\n')
print("numero em hexadecimal:")
print(hex_number)