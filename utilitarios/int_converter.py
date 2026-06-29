def int_to_hex_and_bin_8bit_twos_complement(x):
    mask = 0xFFFFFFFF
    value = x & mask

    hex_value = f"0x{value:02x}"
    bin_value = f"{value:08b}"

    return hex_value, bin_value

x = 1024
hex_val, bin_val = int_to_hex_and_bin_8bit_twos_complement(x)

print("numero em binário:    \n", bin_val)
print("\n")
print("numero em hexadecimal: \n", hex_val)