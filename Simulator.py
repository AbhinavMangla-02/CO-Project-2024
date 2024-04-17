import sys
def sext(imm):
    size=len(imm)
    if imm[0] == '1':
        return '1'*(32-size) + imm
    else:
        return '0'*(32-size) + imm
def int_to_binary(n):
    if n == 0:
        return '0' * 32  # Special case: If n is 0, its binary representation is '000...000'
    elif n < 0:
        # If n is negative, convert it to its binary representation as if it were positive,
        # then remove the leading '-0b' from the result and pad it with leading zeros to make it 32 bits.
        return bin(n & 0xFFFFFFFF)[2:].zfill(32)  # 0xFFFFFFFF is used to ensure a 32-bit representation
    else:
        # Convert positive n to binary, remove the leading '0b', and pad it with leading zeros to make it 32 bits.
        return bin(n)[2:].zfill(32)

def twos_complement(binary_str):
    # Check if the number is negative
    if binary_str[0] == '1':
        # Perform two's complement by flipping the bits and adding 1
        inverted = ''.join('1' if bit == '0' else '0' for bit in binary_str)
        return -(int(inverted, 2) + 1)
    else:
        return int(binary_str, 2)
def signed_bin(number):
    # Convert the number to its binary representation
    binary = bin(number & 0xFFFFFFFF) # Mask with 32 bits to handle negative numbers
    
    # Perform sign extension if necessary
    if number < 0:
        binary = '1' * (32 - len(binary)) + binary
    return binary
class PC:
    index = 0
    binary = ""
    next = 0
    nxt = 0
    lst_idx =0
    def __init__(self,s):
        self.binary = s
        self.index = PC.next
        self.nxt = self.index +4
        PC.next+=4
        PC.lst_idx = self.index
    def update_index(self,n,operand):
        self.index = register_storage[operand] + n
class Memory:
    pntr = 0
    memory_locations = { "0x00010000" : 0 , "0x00010004" : 0 , "0x00010008" : 0 , "0x0001000c" : 0 , "0x00010010":0 ,"0x00010014":0,"0x00010018":0,"0x0001001c":0,"0x00010020":0,"0x00010024":0,"0x00010028":0,"0x0001002c":0,"0x00010030":0,"0x00010034":0,"0x00010038":0,"0x0001003c":0,"0x00010040":0,"0x00010044":0,"0x00010048":0,"0x0001004c":0,"0x00010050":0,"0x00010054":0,"0x00010058":0,"0x0001005c":0,"0x00010060":0,"0x00010064":0,"0x00010068":0,"0x0001006c":0,"0x00010070":0,"0x00010074":0,"0x00010078":0,"0x0001007c":0}
    address_specifier = {  0 : "0x00010000" , 1 : "0x00010004" ,2:"0x00010008" ,3 : "0x0001000c"  ,4: "0x00010010" ,5:"0x00010014",6:"0x00010018", 7: "0x0001001c",8:"0x00010020",9 :"0x001010024",10:"0x00010028",11:"0x0001002c",12:"0x00010030",13:"0x00010034",14:"0x00010038",15:"0x0001003c",16:"0x00010040",17:"0x00010044",18:"0x00010048",19:"0x0001004c",20:"0x00010050",21:"0x00010054",22:"0x00010058",23:"0x0001005c",24:"0x00010060",25:"0x00010064",26:"0x00010068",27:"0x0001006c",28:"0x00010070",29:"0x00010074",30:"0x00010078",31:"0x0001007c"}
    def __init__(self):
        self.pntr = 0
    def store(self,value):
        self.memory_locations[self.address_specifier[self.pntr]] = value
        self.pntr+=1
    def load(self):
        return self.memory_locations[self.address_specifier[self.pntr]]
def add(PC):
    rs1 = reversed_Register_enco[PC.binary[12:17].strip()]
    rs2 = reversed_Register_enco[PC.binary[7:12].strip()]
    rd = reversed_Register_enco[PC.binary[20:25].strip()]
    added_value = register_storage[rs1] + register_storage[rs2]
    register_storage[rd] = added_value

def sub(PC):
    rd = reversed_Register_enco[PC.binary[20:25].strip()]
    rs1 = reversed_Register_enco[PC.binary[12:17].strip()]
    rs2 = reversed_Register_enco[PC.binary[7:12].strip()]
    if rs1 == "zero":
        register_storage[rd] = -register_storage[rs2]
    else:
        register_storage[rd] = register_storage[rs1] - register_storage[rs2]
def sll(PC):
    rd = reversed_Register_enco[PC.binary[20:25].strip()]
    rs1 = reversed_Register_enco[PC.binary[12:17].strip()]
    rs2 = reversed_Register_enco[PC.binary[7:12].strip()]
    rs1_value = register_storage[rs1]
    rs2_value = register_storage[rs2]
    final_decimal = rs1_value << (rs2_value & 0b11111)
    register_storage[rd] = final_decimal


def slt(PC):
    rd = reversed_Register_enco[PC.binary[20:25].strip()]
    rs1 = reversed_Register_enco[PC.binary[12:17].strip()]
    rs2 = reversed_Register_enco[PC.binary[7:12].strip()]
    if register_storage[rs1] < register_storage[rs2]:
        register_storage[rd] = 1
    # ##print('inside slt')
def sltu(PC):
    rd = reversed_Register_enco[PC.binary[20:25].strip()]
    rs1 = reversed_Register_enco[PC.binary[12:17].strip()]
    rs2 = reversed_Register_enco[PC.binary[7:12].strip()]
    value_rs1 = register_storage[rs1]
    value_rs2 = register_storage[rs2]
    if (value_rs1 < 0 and value_rs2 < 0) or (value_rs1 >= 0 and value_rs2 >= 0):
        if value_rs1 < value_rs2:
            register_storage[rd] = 1
    elif value_rs1 >= 0 and value_rs2 < 0:
        register_storage[rd] = 1 
    # ##print('inside sltu')

def xor(PC):
    rd = reversed_Register_enco[PC.binary[20:25].strip()]
    rs1 = reversed_Register_enco[PC.binary[12:17].strip()]
    rs2 = reversed_Register_enco[PC.binary[7:12].strip()]
    final_binary = register_storage[rs1] ^ register_storage[rs2]
    register_storage[rd] = final_binary
    # ##print(register_storage[rd],'xor')
 
def srl(PC):
    rd = reversed_Register_enco[PC.binary[20:25].strip()]
    rs1 = reversed_Register_enco[PC.binary[12:17].strip()]
    rs2 = reversed_Register_enco[PC.binary[7:12].strip()]
    final_binary = register_storage[rs1] >> ((register_storage[rs2]) & 0b11111)
    register_storage[rd] = final_binary
    # ##print(register_storage[rd],'srl')

def orr(PC):
    rd = reversed_Register_enco[PC.binary[20:25].strip()]
    rs1 = reversed_Register_enco[PC.binary[12:17].strip()]
    rs2 = reversed_Register_enco[PC.binary[7:12].strip()]
    final_binary = register_storage[rs1] | register_storage[rs2]
    register_storage[rd] = final_binary
    # ##print(register_storage[rd],'or')
def andd(PC):
    rd = reversed_Register_enco[PC.binary[20:25].strip()]
    rs1 = reversed_Register_enco[PC.binary[12:17].strip()]
    rs2 = reversed_Register_enco[PC.binary[7:12].strip()]
    final_binary = register_storage[rs1] & register_storage[rs2]
    register_storage[rd] = final_binary
    # ##print(register_storage[rd],'and')

def addi(PC):
    destination = reversed_Register_enco[PC.binary[-12:-7].strip()]
    operand1 = reversed_Register_enco[PC.binary[-20:-15].strip()]
    imm= PC.binary[0:12].strip()
    register_storage[destination] = register_storage[operand1] + twos_complement(imm)  
def sltiu(PC):
    destination = reversed_Register_enco[PC.binary[-12:-7].strip()]
    operand1 = reversed_Register_enco[PC.binary[-20:-15].strip()]
    imm= PC.binary[0:12].strip()
    register_storage[destination] = 1 if register_storage[operand1] < int(imm,2) else 0
def sw(PC):
    imm = int(PC.binary[0:7]+PC.binary[20:25],2)
    rs1 = reversed_Register_enco[PC.binary[12:17]]
    memory_int = register_storage[rs1] + imm
    rs2 = reversed_Register_enco[PC.binary[7:12]]
    Memory.memory_locations[Memory.address_specifier[(memory_int-65536)//4]] = register_storage[rs2]
    ##print(Memory.memory_locations[Memory.address_specifier[((memory_int-65536)//4)]],Memory.address_specifier[(memory_int-65536)//4])

def lui(PC):
    imm = (twos_complement(PC.binary[0:20])) << 12
    ##print(int_to_binary(imm))
    ##print(imm)
    rd = reversed_Register_enco[PC.binary[-12:-7]]
    register_storage[rd] = imm

def auipc(PC):
    rd = reversed_Register_enco[PC.binary[-12:-7]]
    imm = (twos_complement(PC.binary[0:20])) << 12
    register_storage[rd] = imm + PC.index
def jal(PC):
    rd = reversed_Register_enco[PC.binary[-12:-7]]
    imm  = twos_complement(PC.binary[12:21] + PC.binary[11] + PC.binary[1:11] + '0')
    ##print(imm)
    register_storage[rd] = PC.index + 4
    PC.nxt = PC.index + imm
    PC.nxt = PC.nxt&0xFFFFFFFE
    # ##print(PC.nxt)
def beq(PC):
    string_imm = PC.binary[-8] + PC.binary[1:7] + PC.binary[-12:-8] + '0'
    imm = twos_complement(string_imm)
    rs2 = reversed_Register_enco[PC.binary[7:12].strip()]
    rs1 = reversed_Register_enco[PC.binary[12:17].strip()]
    if register_storage[rs1] == register_storage[rs2]:
        PC.nxt = PC.index + imm
    else:
        ##print("inside beq else")
        PC.nxt = PC.index + 4


def bne(PC):
    string_imm = PC.binary[-8] + PC.binary[1:7] + PC.binary[-12:-8] + '0'
    ##print(string_imm)
    imm = twos_complement(string_imm)
    ##print(imm)
    rs2 = reversed_Register_enco[PC.binary[7:12].strip()]
    rs1 = reversed_Register_enco[PC.binary[12:17].strip()]
    ##print(register_storage[rs1],register_storage[rs2])
    if register_storage[rs1] != register_storage[rs2]:
        ##print("inside bne")
        PC.nxt = PC.index + imm
    else:
        ##print("inside bne else")
        PC.nxt = PC.index + 4
def blt(PC):
    string_imm = PC.binary[1:7] + PC.binary[-12:-8] + '10'
    if string_imm[0] == '1':
        imm = int(string_imm,2) - 2**12
    else:
        imm = int(string_imm,2)
    rs2 = reversed_Register_enco[PC.binary[7:12].strip()]
    rs1 = reversed_Register_enco[PC.binary[12:17].strip()]
    if register_storage[rs1] < register_storage[rs2]:
        PC.nxt = PC.index + imm
    else:
        ##print("inside bne else")
        PC.nxt = PC.index + 4

def bge(PC):
    string_imm = PC.binary[-8] + PC.binary[1:7] + PC.binary[-12:-8] + '0'
    if string_imm[0] == '1':
        imm = int(string_imm,2) - 2**12
    else:
        imm = int(string_imm,2)
    rs2 = reversed_Register_enco[PC.binary[7:12].strip()]
    rs1 = reversed_Register_enco[PC.binary[12:17].strip()]
    if register_storage[rs1] >= register_storage[rs2]:
        PC.nxt = PC.index + imm
    else:
        ##print("inside bne else")
        PC.nxt = PC.index + 4

def bltu(PC):
    string_imm = PC.binary[-8] + PC.binary[1:7] + PC.binary[-12:-8] + '0'
    if string_imm[0] == '1':
        imm = int(string_imm,2) - 2**12
    else:
        imm = int(string_imm,2)
    rs2 = reversed_Register_enco[PC.binary[7:12].strip()]
    rs1 = reversed_Register_enco[PC.binary[12:17].strip()]
    value_rs1 = register_storage[rs1]
    value_rs2 = register_storage[rs2]
    if (value_rs1 < 0 and value_rs2 < 0) or (value_rs1 >= 0 and value_rs2 >= 0):
        if value_rs1 < value_rs2:
            PC.nxt = PC.index + imm
    elif value_rs1 >= 0 and value_rs2 < 0:
        PC.nxt = PC.index + imm
    else:
        ##print("inside bne else")
        PC.nxt = PC.index + 4

def bgeu(PC):
    string_imm = PC.binary[-8] + PC.binary[1:7] + PC.binary[-12:-8] + '0'
    if string_imm[0] == '1':
        imm = int(string_imm,2) - 2**12
    else:
        imm = int(string_imm,2)
    rs2 = reversed_Register_enco[PC.binary[7:12].strip()]
    rs1 = reversed_Register_enco[PC.binary[12:17].strip()]
    value_rs1 = register_storage[rs1]
    value_rs2 = register_storage[rs2]
    if (value_rs1 < 0 and value_rs2 < 0) or (value_rs1 >= 0 and value_rs2 >= 0):
        if value_rs1 >= value_rs2:
            PC.nxt = PC.index + imm
    elif value_rs1 <= 0 and value_rs2 > 0:
        PC.nxt = PC.index + imm
    else:
        ##print("inside bne else")
        PC.nxt = PC.index + 4
def jalr(PC):
    ##print("inside jalr",PC.index,PC.binary,PC.nxt)
    destination = reversed_Register_enco[PC.binary[-12:-7]]
    imm = twos_complement(PC.binary[0:12])
    ##print(imm,"Imm")
    operand1 = reversed_Register_enco[PC.binary[12:17]]
    register_storage[destination] = PC.index + 4
    PC.nxt = register_storage[operand1] + imm   
    PC.nxt = PC.nxt&0xFFFFFFFE

def lw(PC):
    destination = reversed_Register_enco[PC.binary[-12:-7]]
    operand1 = reversed_Register_enco[PC.binary[-20:-15]]
    imm = PC.binary[0:12]
    register_storage[destination] = Memory.memory_locations[Memory.address_specifier[(register_storage[operand1] + int(imm,2) - 65536)//4]]
def mul(PC):
    rd = reversed_Register_enco[PC.binary[-12:-7]]
    rs1 = reversed_Register_enco[PC.binary[-20:-15]]
    rs2 = reversed_Register_enco[PC.binary[-25:-20]]
    register_storage[rd] = register_storage[rs1] * register_storage[rs2]
    ##print(register_storage[rd])
def reset():
    for i in register_storage:
        register_storage[i] = 0
def rvrs(PC):
    rd = reversed_Register_enco[PC.binary[-12:-7]]
    rs1 = reversed_Register_enco[PC.binary[-20:-15]]
    ##print(register_storage[rs1])
    ##print(int_to_binary(register_storage[rs1]))
    register_storage[rd] = twos_complement((int_to_binary(register_storage[rs1]))[::-1])
    ##print(register_storage[rd])
def Op_R(PC):
    if PC.binary[-7:].strip() == "0110011" and PC.binary[-15:-12].strip() == "000" and PC.binary[0:7] == "0000000":
        add(PC)
    elif PC.binary[-7:].strip() == "0110011" and PC.binary[-15:-12].strip() == "000":
        sub(PC)
    elif PC.binary[-7:].strip() == "0110011" and PC.binary[-15:-12].strip() == "001":
        sll(PC)
    elif PC.binary[-7:].strip() == "0110011" and PC.binary[-15:-12].strip() == "010":
        slt(PC)
    elif PC.binary[-7:].strip() == "0110011" and PC.binary[-15:-12].strip() == "011":
        sltu(PC)
    elif PC.binary[-7:].strip() == "0110011" and PC.binary[-15:-12].strip() == "100":
        xor(PC)
    elif PC.binary[-7:].strip() == "0110011" and PC.binary[-15:-12].strip() == "101":
        srl(PC)
    elif PC.binary[-7:].strip() == "0110011" and PC.binary[-15:-12].strip() == "110":
        orr(PC)
    elif PC.binary[-7:].strip() == "0110011" and PC.binary[-15:-12].strip() == "111":
        andd(PC)
    else:
        print("Invalid Instruction")

def Op_I(PC):
    if PC.binary[-7:].strip() == "0000011":
        lw(PC)
    elif PC.binary[-7:].strip() == "0010011" and PC.binary[-15:-12].strip() == "000":
        addi(PC)
    elif PC.binary[-7:].strip() == "1100111":
        jalr(PC)
    elif PC.binary[-7:].strip() == "0010011":
        sltiu(PC)
    else:
        print("Invalid Instruction")

def Op_B(PC):
    if PC.binary[-7:].strip() == "1100011" and PC.binary[-15:-12].strip() == "000":
        beq(PC)
    elif PC.binary[-7:].strip() == "1100011" and PC.binary[-15:-12].strip() == "001":
        bne(PC)
    elif PC.binary[-7:].strip() == "1100011" and PC.binary[-15:-12].strip() == "100":
        blt(PC)
    elif PC.binary[-7:].strip() == "1100011" and PC.binary[-15:-12].strip() == "101":
        bge(PC)
    elif PC.binary[-7:].strip() == "1100011" and PC.binary[-15:-12].strip() == "110":
        bltu(PC)
    elif PC.binary[-7:].strip() == "1100011" and PC.binary[-15:-12].strip() == "111":
        bgeu(PC)
    else:
        print("Invalid Instruction")

def Op_S(PC):
    if PC.binary[-7:].strip() == "0100011":
        sw(PC)
    else:
        print("Invalid Instruction")

def Op_U(PC):
    if PC.binary[-7:].strip() == "0110111":
        lui(PC)
    elif PC.binary[-7:].strip() == "0010111":
        auipc(PC)
    else:
        print("Invalid Instruction")

def Op_J(PC):
    if PC.binary[-7:].strip() == "1101111":
        jal(PC)
    else:
        print("Invalid Instruction")
def OP_A(PC):
    if PC.binary[-7:].strip() == "0000001":
        # print("mul called")
        mul(PC)
    elif PC.binary[-7:].strip() == "0000010":
        reset()
        ##print("reset called")
    elif PC.binary[-7:].strip() == "0000100":
        ##print("rvrs called")
        rvrs(PC)
    else:
        print("Invalid Instruction")
file =  open(sys.argv[1],'r')
lines = []
lines = file.readlines()
for line in lines:
    line = line.strip()
program = []
for line in lines:
    program.append(PC(line.strip()))
# for p in program:
#     ##print(p.index , p.binary, end = "")

# Program Storages :: --
file.close()
register_storage = {
    "zero": 0,
    "ra": 0,
    "sp": 256,
    "gp": 0,
    "tp": 0,
    "t0": 0,
    "t1": 0,
    "t2": 0,
    "s0": 0,
    "s1": 0,
    "a0": 0,
    "a1": 0,
    "a2": 0,
    "a3": 0,
    "a4": 0,
    "a5": 0,
    "a6": 0,
    "a7": 0,
    "s2": 0,
    "s3": 0,
    "s4": 0,
    "s5": 0,
    "s6": 0,
    "s7": 0,
    "s8": 0,
    "s9": 0,
    "s10": 0,
    "s11": 0,
    "t3": 0,
    "t4": 0,
    "t5": 0,
    "t6": 0
}
# opcode to instruction type::--\
reversed_opcode = {
    "0110011": 'R',
    "0010011": 'I',
    "0000011": 'I',
    "0100011": 'S',
    "1100111": 'I',
    "1100011": 'B',
    "0110111": 'U',
    "0010111": 'U',
    "1101111": 'J',
    "0000001": 'A',
    "0000010": 'A',
    "0000100": 'A'
}
reversed_funct3 = {
    "000": ["add", "sub", "addi", "jalr", "beq", "lui", "auipc", "jal"],
    "001": ["sll", "bne"],
    "010": ["slt", "lw", "sw"],
    "011": ["sltu", "sltiu"],
    "100": ["xor", "blt"],
    "101": ["srl", "bge"],
    "110": ["or", "bltu"],
    "111": ["and", "bgeu"]
}
reversed_funct7 = {
    "0000000": ["add", "sll", "slt", "sltu", "xor", "srl", "or", "and"],
    "0100000": ["sub"]
}

reversed_Register_enco = {
    "00000": "zero",
    "00001": "ra",
    "00010": "sp",
    "00011": "gp",
    "00100": "tp",
    "00101": "t0",
    "00110": "t1",
    "00111": "t2",
    "01000": "s0",
    "01001": "s1",
    "01010": "a0",
    "01011": "a1",
    "01100": "a2",
    "01101": "a3",
    "01110": "a4",
    "01111": "a5",
    "10000": "a6",
    "10001": "a7",
    "10010": "s2",
    "10011": "s3",
    "10100": "s4",
    "10101": "s5",
    "10110": "s6",
    "10111": "s7",
    "11000": "s8",
    "11001": "s9",
    "11010": "s10",
    "11011": "s11",
    "11100": "t3",
    "11101": "t4",
    "11110": "t5",
    "11111": "t6"
}
PC_dict = {}
end = 0
for i in program:
    PC_dict[i.index] = i.binary
    end = max(end,i.index)
    ##print(i.binary,i.index,i.nxt)
# ##print(PC_dict)
# ##print(PC_dict[-1].key)
# ##print(end)
output_file = open(sys.argv[2],'w')
count = 0
c1 = 1
while(count <= end):
    ##print(c1 , count , end)
    c1 = c1+1 
    register_storage["zero"] = 0
    if program[count//4].binary == "00000000000000000000000001100011":
        # for m in register_storage:
        output_file.write(f"0b{format(program[count//4].nxt-4,'032b')} ")
        for m in register_storage:
            output_file.write(f"0b{int_to_binary(register_storage[m])} ")
        output_file.write(f"\n")
        ###print(True , "LOOP ENDED")
        #     ##print(m,register_storage[m])
        break
    if program[count//4].binary == "00000000000000000000000000000011":
        ##print("HALT CALLED")
        output_file.write(f"0b{format(program[count//4].nxt,'032b')} ")
        for m in register_storage:
            output_file.write(f"0b{format(register_storage[m],'032b')} ")
        output_file.write(f"\n")
        break
    ###print(count," count")
    ###print(program[count//4].binary)
    ###print(program[count//4].index)
    ###print(program[count//4].nxt)
    if reversed_opcode[program[count//4].binary[-7:].strip()] == 'R':
        Op_R(program[count//4])
    elif reversed_opcode[program[count//4].binary[-7:].strip()] == 'I':
        Op_I(program[count//4])
    elif reversed_opcode[program[count//4].binary[-7:].strip()] == 'S':
        Op_S(program[count//4])
    elif reversed_opcode[program[count//4].binary[-7:].strip()] == 'B':
        Op_B(program[count//4])
        b_type = True
        # ##print(program[count//4].nxt)
        # break
    elif reversed_opcode[program[count//4].binary[-7:].strip()] == 'U':
        Op_U(program[count//4])
    elif reversed_opcode[program[count//4].binary[-7:].strip()] == 'J':
        Op_J(program[count//4])
    elif reversed_opcode[program[count//4].binary[-7:].strip()] == 'A':
        OP_A(program[count//4])
        # break
    # ##print(count)
    # ##print(program[count//4].binary,program[count//4].index,program[count//4].nxt,program[count//4].nxt)
    ###print(program[count//4].nxt)
    output_file.write(f"0b{format(program[count//4].nxt,'032b')} ")
    if program[count//4].nxt != 0:
        count = program[count//4].nxt
    else:
        count+=4
    ###print(count)
    # for m in register_storage:
    #     ##print(m,register_storage[m])
    ##print("zero",register_storage["zero"] , "ra : " , register_storage["ra"] , "s0 : " ,register_storage["s0"] , "s1 : " ,register_storage["s1"] , "s2 : " ,register_storage["s2"] , "s3 : " ,register_storage["s3"] , "t0 : " , register_storage["t0"] )
    register_storage["zero"] = 0
    ###print(program[count//4].nxt)
    for m in register_storage:
        output_file.write(f"0b{int_to_binary(register_storage[m])} ")
    output_file.write(f"\n")
# fo    r n in program:
#         ##print(n.binary, n.next,n.nxt)
for i in Memory.memory_locations:
    output_file.write(f"{i}:0b{int_to_binary(Memory.memory_locations[i])}\n")
output_file.close()
