#include<bits/stdc++.h>
using namespace std;
int bin_to_dec(string s)
{
    int ans = 0;
    for(int i=s.length()-1;i>=0 ;i--)
    {
        ans+= (s[i]-'0')*pow(2,s.length()-i-1);
    }
    return ans;
}
void add(map<string,int> &reg_stor, string rd , string rs1,string rs2)
{
    reg_stor[rd] = reg_stor[rs1] + reg_stor[rs2];
}
int main()
{
    map<string,string> opcode;
        {
            opcode["add"]="0110011";
            opcode["sub"]="0110011";
            opcode["sll"]="0110011";
            opcode["slt"]="0110011";
            opcode["sltu"]="0110011";
            opcode["xor"]="0110011";
            opcode["srl"]="0110011";
            opcode["or"]="0110011";
            opcode["and"]="0110011";
            opcode["addi"]="0010011";
            opcode["sltiu"]="0010011";
            opcode["lw"]="0000011";
            opcode["sw"]="0100011";
            opcode["jalr"]="1100111";
            opcode["beq"]="1100011";
            opcode["bne"]="1100011";
            opcode["blt"]="1100011";
            opcode["bge"]="1100011";
            opcode["bltu"]="1100011";
            opcode["bgeu"]="1100011";
            opcode["lui"]="0110111";
            opcode["auipc"]="0010111";
            opcode["jal"]="1101111";
            // for Bonus Question you just have to make the mul , rst , halt,rvrs here , you have to make opcode yourself

        }
    map<string,string> Register_enco;
    {
        Register_enco["zero"]="00000";
        Register_enco["ra"]="00001";
        Register_enco["sp"]="00010";
        Register_enco["gp"]="00011";
        Register_enco["tp"]="00100";
        Register_enco["t0"]="00101";
        Register_enco["t1"]="00110";
        Register_enco["t2"]="00111";
        Register_enco["s0"]="01000";
        Register_enco["s1"]="01001";
        Register_enco["a0"]="01010";
        Register_enco["a1"]="01011";
        Register_enco["a2"]="01100";
        Register_enco["a3"]="01101";
        Register_enco["a4"]="01110";
        Register_enco["a5"]="01111";
        Register_enco["a6"]="10000";
        Register_enco["a7"]="10001";
        Register_enco["s2"]="10010";
        Register_enco["s3"]="10011";
        Register_enco["s4"]="10100";
        Register_enco["s5"]="10101";
        Register_enco["s6"]="10110";
        Register_enco["s7"]="10111";
        Register_enco["s8"]="11000";
        Register_enco["s9"]="11001";
        Register_enco["s10"]="11010";
        Register_enco["s11"]="11011";
        Register_enco["t3"]="11100";
        Register_enco["t4"]="11101";
        Register_enco["t5"]="11110";
        Register_enco["t6"]="11111";
    }
    map<string,string> funct3;
    {
        funct3["add"]="000";
        funct3["sub"]="000";
        funct3["sll"]="001";
        funct3["slt"]="010";
        funct3["sltu"]="011";
        funct3["xor"]="100";
        funct3["srl"]="101";
        funct3["or"]="110";
        funct3["and"]="111";
        funct3["addi"]="000";
        funct3["sltiu"]="011";
        funct3["lw"]="010";
        funct3["sw"]="010";
        funct3["jalr"]="000";
        funct3["beq"]="000";
        funct3["bne"]="001";
        funct3["blt"]="100";
        funct3["bge"]="101";
        funct3["bltu"]="110";
        funct3["bgeu"]="111";
        funct3["lui"]="000";
        funct3["auipc"]="000";
        funct3["jal"]="000";
    }
    map<string,string> funct7;
    {
        funct7["add"]="0000000";
        funct7["sub"]="0100000";
        funct7["sll"]="0000000";
        funct7["slt"]="0000000";
        funct7["sltu"]="0000000";
        funct7["xor"]="0000000";
        funct7["srl"]="0000000";
        funct7["or"]="0000000";
        funct7["and"]="0000000";
    }
    map<string,char> ins_type;
    {
        ins_type["add"]='R';
        ins_type["sub"]='R';
        ins_type["sll"]='R';
        ins_type["slt"]='R';
        ins_type["sltu"]='R';
        ins_type["xor"]='R';
        ins_type["srl"]='R';
        ins_type["or"]='R';
        ins_type["and"]='R';
        ins_type["addi"]='I';
        ins_type["sltiu"]='I';
        ins_type["sw"]='S';
        ins_type["lw"]='I';
        ins_type["jalr"]='I';
        ins_type["beq"]='B';
        ins_type["bne"]='B';
        ins_type["blt"]='B';
        ins_type["bge"]='B';
        ins_type["bltu"]='B';
        ins_type["bgeu"]='B';
        ins_type["lui"]='U';
        ins_type["auipc"]='U';
        ins_type["jal"]='J';
    }
    map<string,int> register_storage;
    {
        register_storage["zero"]=0;
        register_storage["ra"]=0;
        register_storage["sp"]=0;
        register_storage["gp"]=0;
        register_storage["tp"]=0;
        register_storage["t0"]=0;
        register_storage["t1"]=0;
        register_storage["t2"]=0;
        register_storage["s0"]=0;
        register_storage["s1"]=0;
        register_storage["a0"]=0;
        register_storage["a1"]=0;
        register_storage["a2"]=0;
        register_storage["a3"]=0;
        register_storage["a4"]=0;
        register_storage["a5"]=0;
        register_storage["a6"]=0;
        register_storage["a7"]=0;
        register_storage["s2"]=0;
        register_storage["s3"]=0;
        register_storage["s4"]=0;
        register_storage["s5"]=0;
        register_storage["s6"]=0;
        register_storage["s7"]=0;
        register_storage["s8"]=0;
        register_storage["s9"]=0;
        register_storage["s10"]=0;
        register_storage["s11"]=0;
        register_storage["t3"]=0;
        register_storage["t4"]=0;
        register_storage["t5"]=0;
        register_storage["t6"]=0;
    }
    std::ifstream input_file;
    input_file.open("i.txt");
    if (!input_file.is_open()) {
        cout << "Error opening input file: " << endl;

    }
    ofstream output_file;
    output_file.open("Output.txt");
    if (!output_file.is_open()) {
        cout << "Error opening output file!" << endl;
    }
    string line;
while(input_file.eof()==0)
    {
    vector<string> v;
    while (getline(input_file, line)) 
    {
        v.clear();
        // cout << "read line: " << line << "\n" ;
        if (line == "") 
        {
            continue;
        }
        // Creates the vector of different strings containing the Instruction and Registers
        string word = "";
        for (int it = 0; it < line.length(); it++) 
        {
            // cout << "inside loop \n" ;
            if (line[it] == ' ' || line[it] == ',') 
            {
                if (word != "") 
                {
                    v.push_back(word);
                    word = "";
                }
            } 
            else 
            {
                word += line[it];
                cout << "word = " << word << endl;
            }
        }
        if (word != "") 
        {
            v.push_back(word);
        }
    }
        // If the instruction is R type

        // for(auto it : v)
        // {
        //     cout << it << " " ;
        // }
        // cout << endl;
        if(ins_type[v[0]]=='R')
        {
            cout << "IF ENTERED R TYPE\n";
            string output = "";
            output+=opcode[v[0]];
            string rd = Register_enco[v[1]];
            string rs1 = Register_enco[v[2]];
            string rs2 = Register_enco[v[3]];
            output+=rd;
            output+=funct3[v[0]];
            output+=rs1;
            output+=rs2;
            output+=funct7[v[0]];
            add(register_storage,rd,rs1,rs2);
            output_file<<output<<endl;    
        }
    }
    input_file.close();
    output_file.close();
    }
