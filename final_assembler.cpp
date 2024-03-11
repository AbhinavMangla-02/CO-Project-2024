#include<bits/stdc++.h>
using namespace std;

class PC
{
public:
    string ins;
    int index = 0;
    vector<string> tokens_in_ins;
    PC(string ins)
    {
        static int next = 0;
        this->ins = ins;
        this->index = next;
        next += 4;
    }
    void covert_to_tokens()
    {
        string word = "";
        for (auto &it2 : this->ins)
        {
            if (it2 == ' ' || it2 == ',' || it2 == '(' || it2 == ')')
            {
                if(word ==" ")
                {
                    continue;
                }
                else if (word != " " && word != "")
                {
                    this->tokens_in_ins.push_back(word);
                    word = "";
                }
            }
            else
            {
                word += it2;
            }
        }
        if(word!= "")
        {
            this->tokens_in_ins.push_back(word);
            word = "";
        }
    
    }
    void print_tokens()
    {
        cout << this->index << " ";
        for (int i = 0; i < this->tokens_in_ins.size(); i++)
        {
            cout << this->tokens_in_ins[i] << " ";
        }
        cout << endl;
    }
    bool check_and_correct_R(map<string,string> ins_type, map<string,string> register_enco)
    {
        if(ins_type.find(this->tokens_in_ins[0]) == ins_type.end() || register_enco.find(this->tokens_in_ins[1]) == register_enco.end() || register_enco.find(this->tokens_in_ins[2]) == register_enco.end() || register_enco.find(this->tokens_in_ins[3]) == register_enco.end())
        {
            return false;
        }
        return true;
    }
    bool check_and_correct_I(map<string,string> ins_type, map<string,string> register_enco)
    {
        if(ins_type.find(this->tokens_in_ins[0]) == ins_type.end())
        {
            return false;
        }
        else
        {
            if(this->tokens_in_ins[0] == "lw")
            {
                if(register_enco.find(this->tokens_in_ins[1]) == register_enco.end() || register_enco.find(this->tokens_in_ins[3]) == register_enco.end() || stoi(this->tokens_in_ins[2]) > 4095 || stoi(this->tokens_in_ins[2]) < -4096)
                {
                    return false;
                }
            }
            else if(this->tokens_in_ins[0] == "jalr" || this->tokens_in_ins[0] == "addi" || this->tokens_in_ins[0] == "sltiu")
            {
                if(register_enco.find(this->tokens_in_ins[1]) == register_enco.end() || register_enco.find(this->tokens_in_ins[2]) == register_enco.end()  || stoi(this->tokens_in_ins[3]) > 4095 || stoi(this->tokens_in_ins[3]) < -4096)
                {
                    return false;
                }
            }
        }
        return true;
    }
    bool check_and_correct_S(map<string,string> ins_type, map<string,string> register_enco)
    {
        if(ins_type.find(this->tokens_in_ins[0]) == ins_type.end() || register_enco.find(this->tokens_in_ins[1]) == register_enco.end() || register_enco.find(this->tokens_in_ins[3]) == register_enco.end() || stoi(this->tokens_in_ins[2]) >  2047 || stoi(this->tokens_in_ins[2]) < -2048)
        {
            return false;
        }
        return true;
    }
    bool check_and_correct_B(map<string,string> ins_type, map<string,string> register_enco)
    {
        if(ins_type.find(this->tokens_in_ins[0]) == ins_type.end() || register_enco.find(this->tokens_in_ins[1]) == register_enco.end() || register_enco.find(this->tokens_in_ins[2]) == register_enco.end() || stoi(this->tokens_in_ins[3]) > 4095 || stoi(this->tokens_in_ins[3]) < -4096)
        {
            return false;
        }
        return true;
    }
    bool check_and_correct_B(map<string,string> ins_type, map<string,string> register_enco,map<string,int> label)
    {
        if(ins_type.find(this->tokens_in_ins[0]) == ins_type.end() || register_enco.find(this->tokens_in_ins[1]) == register_enco.end() || register_enco.find(this->tokens_in_ins[2]) == register_enco.end())
        {
            return false;
        }
        return true;
    }
    bool check_and_correct_U(map<string,string> ins_type, map<string,string> register_enco)
    {
        if(ins_type.find(this->tokens_in_ins[0]) == ins_type.end() || register_enco.find(this->tokens_in_ins[1]) == register_enco.end() || stoi(this->tokens_in_ins[2]) > 2147483647 || stoi(this->tokens_in_ins[2]) < -2147483648)
        {
            return false;
        }
        return true;
    }
    bool check_and_correct_J(map<string,string> ins_type, map<string,string> register_enco)
    {
        if(ins_type.find(this->tokens_in_ins[0]) == ins_type.end() || register_enco.find(this->tokens_in_ins[1]) == register_enco.end() || stoi(this->tokens_in_ins[2]) > 1048575|| stoi(this->tokens_in_ins[2]) < -1048576)
        {
            return false;
        }
        return true;
    }
    bool check_and_correct_J(map<string,string> ins_type, map<string,string> register_enco,map<string,int> label)
    {
        if(ins_type.find(this->tokens_in_ins[0]) == ins_type.end() || register_enco.find(this->tokens_in_ins[1]) == register_enco.end())
        {
            return false;
        }
        return true;
    }
    bool check_and_correct(map<string,string> ins_type, map<string,string> register_enco,map<string,int> label)
    {
        if(ins_type[this->tokens_in_ins[0]] == "R")
        {
            return this->check_and_correct_R(ins_type,register_enco);
        }
        else if(ins_type[this->tokens_in_ins[0]] == "I")
        {
            return this->check_and_correct_I(ins_type,register_enco);
        }
        else if(ins_type[this->tokens_in_ins[0]] == "S")
        {
            return this->check_and_correct_S(ins_type,register_enco);
        }
        else if(ins_type[this->tokens_in_ins[0]] == "B" && label.find(this->tokens_in_ins[3]) == label.end())
        {
            return this->check_and_correct_B(ins_type,register_enco);
        }
        else if(ins_type[this->tokens_in_ins[0]] == "B")
        {
            return this->check_and_correct_B(ins_type,register_enco,label);
        }
        else if(ins_type[this->tokens_in_ins[0]] == "U")
        {
            return this->check_and_correct_U(ins_type,register_enco);
        }
        else if(ins_type[this->tokens_in_ins[0]] == "J" && label.find(this->tokens_in_ins[2]) == label.end())
        {
            return this->check_and_correct_J(ins_type,register_enco);
            cout << "Its here" ;
        }
        else if(ins_type[this->tokens_in_ins[0]] == "J")
        {
            return this->check_and_correct_J(ins_type,register_enco, label);
            cout << "Its here" ;

        }
        else
        {
            return false;
        }
    }
};
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

    map<string,string> ins_type;
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
    vector<PC> program;
    ifstream file("input.txt");
    string line;
    while (getline(file, line))
    {
        program.push_back(PC(line));
    }
    file.close();
    bool error = false;
    map<string,int> label;
    for(auto &it:program)
    {
        it.covert_to_tokens();
    }
    for(auto &it : program)
    {
        if(it.tokens_in_ins[0][it.tokens_in_ins[0].size()-1] == ':')
        {
            label[it.tokens_in_ins[0].substr(0,it.tokens_in_ins[0].size()-1)] = it.index;
            it.tokens_in_ins.erase(it.tokens_in_ins.begin());
        }
        else
        {
            string temp = ins_type[it.tokens_in_ins[0]];
            if(temp != "R" && temp != "S" && temp != "U" && temp != "I" && temp != "B" && temp != "J")
            {
                error = true;
                cout << "Error in the instruction at Line " << it.index/4 << endl;
                break;
            }
        }
    }

    ofstream file2("Output.txt");
    for(auto &it:program)
    {
        if((error!= true) && (it.check_and_correct(ins_type,Register_enco,label) == false))
        {
            error = true;
            cout << "Error in the instruction at Line " << it.index/4 << endl;
            break;
        }
    }
    if(error == false)
    {
        for(int i = 0 ; i < program.size()-1 ; i++)
        {
            if(program[i].tokens_in_ins[0] == "beq" && program[i].tokens_in_ins[1]  == "zero" && program[i].tokens_in_ins[2]  == "zero" && program[i].tokens_in_ins[3] == "0")
            {
                error = true;
                cout << "ERROR : beq zero,zero,0 -- present before last Line" << endl;
                break;
            }
        }
        if(error == false && program[program.size()-1].tokens_in_ins[0] != "beq" && program[program.size()-1].tokens_in_ins[1]  != "zero" && program[program.size()-1].tokens_in_ins[2]  != "zero" && program[program.size()-1].tokens_in_ins[3] != "0")
        {
            error = true;
            cout << "ERROR : beq zero,zero,0 -- Missing from program" << endl;
        }
    }
    if(error == false)
        {
            for(auto &it:program)
                {
                    string temp_binary = "";
                    if(ins_type[it.tokens_in_ins[0]] == "R")
                    {
                        temp_binary += funct7[it.tokens_in_ins[0]];
                        temp_binary += Register_enco[it.tokens_in_ins[3]];
                        temp_binary += Register_enco[it.tokens_in_ins[2]];
                        temp_binary += funct3[it.tokens_in_ins[0]];
                        temp_binary += Register_enco[it.tokens_in_ins[1]];
                        temp_binary += opcode[it.tokens_in_ins[0]];
                    }
                    else if (ins_type[it.tokens_in_ins[0]] == "B")
                    {
                        string data = "";
                        if(label.find(it.tokens_in_ins[3]) != label.end())
                        {
                            int offset =  it.index - label[it.tokens_in_ins[3]];
                            data = bitset<13>(offset).to_string();
                        }
                        else
                        {
                            int offset = stoi(it.tokens_in_ins[3]);
                            data = bitset<13>(offset).to_string();
                        }
                        temp_binary += data[0];
                        for(int i = 2 ; i < 8 ; i++)
                        {
                            temp_binary += data[i];
                        }
                        temp_binary += Register_enco[it.tokens_in_ins[2]];
                        temp_binary += Register_enco[it.tokens_in_ins[1]];
                        temp_binary += funct3[it.tokens_in_ins[0]];
                        for(int i = 8 ; i < 12 ; i++)
                        {
                            temp_binary += data[i];
                        }
                        temp_binary += data[1];
                        temp_binary += opcode[it.tokens_in_ins[0]];
                    }
                    else if(ins_type[it.tokens_in_ins[0]] == "U")
                    {
                        string data = (bitset<32>(stoi(it.tokens_in_ins[2])).to_string()).substr(0,20);
                        temp_binary += data;
                        temp_binary += Register_enco[it.tokens_in_ins[1]];
                        temp_binary += opcode[it.tokens_in_ins[0]];
                    }
                    else if(ins_type[it.tokens_in_ins[0]] == "J")
                    {
                        string data = "";
                        if(label.find(it.tokens_in_ins[2]) != label.end())
                        {
                            int offset =  it.index - label[it.tokens_in_ins[2]];
                            data = bitset<21>(offset).to_string();
                        }
                        else
                        {
                            int offset = stoi(it.tokens_in_ins[2]);
                            data = bitset<21>(offset).to_string();
                        }
                        temp_binary += data[0];
                        for(int i = 10 ; i < 20 ; i++)
                        {
                            temp_binary += data[i];
                        }
                        temp_binary += data[9];
                        for(int i = 1 ; i < 9 ; i++)
                        {
                            temp_binary += data[i];
                        }
                        temp_binary += Register_enco[it.tokens_in_ins[1]];
                        temp_binary += opcode[it.tokens_in_ins[0]];
                    }
                    else if (ins_type[it.tokens_in_ins[0]] == "S")
                    {
                        int offset = stoi(it.tokens_in_ins[2]);
                        string imm = bitset<12>(offset).to_string();
                        for (int i = 0; i <= 6; i++)
                        {
                            temp_binary += imm[i];
                        }
                        temp_binary += Register_enco[it.tokens_in_ins[1]];
                        temp_binary += Register_enco[it.tokens_in_ins[3]];
                        temp_binary += funct3[it.tokens_in_ins[0]];
                        for (int i = 7; i <= 11; i++)
                        {
                            temp_binary += imm[i];
                        }
                        temp_binary += opcode[it.tokens_in_ins[0]];
                    }
                    else if(ins_type[it.tokens_in_ins[0]] == "I")
                    {
                        string data = "";
                        if(it.tokens_in_ins[0] == "lw")
                        {
                            int offset = stoi(it.tokens_in_ins[2]);
                            string imm = bitset<12>(offset).to_string();
                            temp_binary += imm;
                            temp_binary += Register_enco[it.tokens_in_ins[3]];
                            temp_binary += funct3[it.tokens_in_ins[0]];
                            temp_binary += Register_enco[it.tokens_in_ins[1]];
                            temp_binary += opcode[it.tokens_in_ins[0]];
                        }
                        else if(it.tokens_in_ins[0] == "jalr" || it.tokens_in_ins[0] == "addi" || it.tokens_in_ins[0] == "sltiu")
                        {
                            int offset = stoi(it.tokens_in_ins[3]);
                            string imm = bitset<12>(offset).to_string();
                            temp_binary += imm;
                            temp_binary += Register_enco[it.tokens_in_ins[2]];
                            temp_binary += funct3[it.tokens_in_ins[0]];
                            temp_binary += Register_enco[it.tokens_in_ins[1]];
                            temp_binary += opcode[it.tokens_in_ins[0]];
                        }
                    }
                    file2 << temp_binary << endl;
                }
        }
    file2.close();
}
