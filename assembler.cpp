#include <bits/stdc++.h>
#include <fstream>
#include <bitset>


using namespace std;

string string_to_bin(string s)
{
    int num = 0;
    if(s[0] == '-')
    {
        for(int i = 1 ;i < s.length() ;i++)
        {
            num = num*10+ (s[i]-'0');
        }
        num = -1*(num);
    }
    else
    {
        for(int i = 0 ;i < s.length() ;i++)
        {
            num = num*10+ (s[i]-'0');
        }
    }

    // cout << num << endl;
    // string ans = "";
    if (num > 2047 || num < -2048)
    {
        return "Error";
    }
    bitset<12> imm_whole(num);
    string ans = imm_whole.to_string();
    return ans;
}
string string_to_bin_Jtype(string s)
{
    int num = 0;
    if(s[0] == '-')
    {
        for(int i = 1 ;i < s.length() ;i++)
        {
            num = num*10+ (s[i]-'0');
        }
        num = -1*(num);
    }
    else
    {
        for(int i = 0 ;i < s.length() ;i++)
        {
            num = num*10+ (s[i]-'0');
        }
    }

    // cout << num << endl;
    // string ans = "";
    // if (num > 2047 || num < -2048)
    // {
    //     return "Error";
    // }
    bitset<20> imm_whole(num);
    string ans = imm_whole.to_string();
    return ans;
}
string check_and_convert(string tocheck, map<string, string> checker, string &isError)
{
    if (checker.find(tocheck)==checker.end())
    {
        isError = "True";
    }
    return checker[tocheck];
}


string Utype_to_binary(vector<string> vtemp, map<string,string> opcode, map<string,string> Register_enco)
{
    string is_error = "False";
    string output = "";
    string rd = check_and_convert(vtemp[1], Register_enco, is_error);
    int decimal_value = stoi(vtemp[2]);
    if (decimal_value > 1048575 || decimal_value < -1048576)
    {
        return "Error";
    }
    bitset<20> imm_whole(decimal_value);
    string imm_whole_final = imm_whole.to_string();
    output += imm_whole_final;
    output += rd;
    output += check_and_convert(vtemp[0], opcode, is_error);
    if (is_error=="False") return output;
    else return "Error";
}
string Btype_to_binary(vector<string> vtemp, map<string,string> opcode, map<string,string> Register_enco, map<string,string> funct3)
{
    string is_error = "False";
    string output = "";
    vtemp[3] = string_to_bin(vtemp[3]);
    // cout << vtemp[3] ;
    // cout << vtemp[3] << endl;
    for(int i =0 ; i < 7 ; i++)
    {
        output+=vtemp[3][i];
        // cout << vtemp[3][i];
    }
    // cout << endl;
    // // output+=" ";
    string rs2 = check_and_convert(vtemp[2], Register_enco, is_error);
    string rs1 = check_and_convert(vtemp[1], Register_enco, is_error);
    // cout << rs2 << " " << rs1 << endl;
    // output+=" ";
    output+=rs2;
    // output+=" ";
    output+=rs1;
    // cout << funct3[vtemp[0]] << endl;
    output+=check_and_convert(vtemp[0], funct3, is_error);
    // output+=" ";
    // output+=" ";
    for(int i =7 ; i < 12 ; i++)
    {
        output+=vtemp[3][i];
    //    cout << vtemp[3][i];
    }
    // cout << endl;
    output+=check_and_convert(vtemp[0], opcode, is_error);
    if (is_error=="False") return output;
    else return "Error";
}

string Rtype_to_binary(vector<string> vtemp, map<string,string> opcode, map<string,string> Register_enco, map<string,string> funct3, map<string,string> funct7)
{
    string is_error = "False";
    string output = "";
    string rd = check_and_convert(vtemp[1], Register_enco, is_error);
    string rs1 = check_and_convert(vtemp[2], Register_enco, is_error);
    string rs2 = check_and_convert(vtemp[3], Register_enco, is_error);
    output+=check_and_convert(vtemp[0], funct7, is_error);
    output+=rs2;
    output+=rs1;
    output+=check_and_convert(vtemp[0], funct3, is_error);
    output+=rd;
    output+=check_and_convert(vtemp[0], opcode, is_error);
    if (is_error=="False") return output;
    else return "Error";
}
string Itype_to_binary(vector<string> vtemp, map<string,string> opcode, map<string,string> Register_enco, map<string,string> funct3,string rs1, string imm)
{
    string is_error = "False";
    string output = "";
    output+=imm;
    // output+=" ";
    // string rs2 = check_and_convert(vtemp[2], Register_enco, is_error);
    string rd = check_and_convert(vtemp[1], Register_enco, is_error);
    output+=Register_enco[rs1];
    // output+=" ";
    output+=funct3[vtemp[0]];
    // output+=" ";
    output+=rd;
    // output+=" ";
    output+=check_and_convert(vtemp[0], opcode, is_error);
    if (is_error=="False") return output;
    else return "Error";
}
string Itype_to_binary(vector<string> vtemp, map<string,string> opcode, map<string,string> Register_enco, map<string,string> funct3)
{
    string is_error = "False";
    string output = "";
    // cout << vtemp[3] << endl;
    output+=string_to_bin(vtemp[3]);
    cout << output << endl;
    // output+=" ";
    string rs2 = check_and_convert(vtemp[2], Register_enco, is_error);
    string rd = check_and_convert(vtemp[1], Register_enco, is_error);
    output+=rs2;
    // output+=" ";
    output+=check_and_convert(vtemp[0], funct3, is_error);
    // output+=" ";
    output+=rd;
    // output+=" ";
    output+=check_and_convert(vtemp[0], opcode, is_error);
    if (is_error=="False") return output;
    else return "Error";
}

string Stype_to_binary(vector<string> vtemp, map<string,string> opcode, map<string,string> Register_enco, map<string,string> funct3)
{
    string is_error = "False";
    string output = "";
    string rs1 = check_and_convert(vtemp[3], Register_enco, is_error);
    string rs2 = check_and_convert(vtemp[1], Register_enco, is_error);
    int decimal_value = stoi(vtemp[2]);
    if (decimal_value > 2047 || decimal_value < -2048)
    {
        return "Error";
    }
    bitset<12> imm_whole(decimal_value);
    string imm_whole_final = imm_whole.to_string();
    string imm_0_to_4 = imm_whole_final.substr(7,5);
    string imm_5_to_11 = imm_whole_final.substr(0,7);
    output += imm_5_to_11;
    output += rs2;
    output += rs1;
    output += check_and_convert(vtemp[0], funct3, is_error);
    output += imm_0_to_4;
    output += check_and_convert(vtemp[0], opcode, is_error);
    if (is_error=="False") return output;
    else return "Error";
}
string Jtype_to_binary(vector<string> vtemp, map<string,string> opcode, map<string,string> Register_enco)
{
    string is_error = "False";
    string output = "";
    string data = string_to_bin_Jtype(vtemp[2]);
    cout << data;
    output += data[0];
    for(int i = 9 ; i <= 19 ; i++)
    {
        output+=data[i];
    }
    for(int i = 1 ; i <= 8 ; i++)
    {
        output+=data[i];
    }
    // output+=data[10];
    // for(int i = 11 ; i <=19 ; i++)
    // {
    //     output+=data[i];
    // }
    // for(int i =10 ; i < 20 ; i++)
    // {
    //     output+=vtemp[2][i];
    // }
    // cout << data << endl;
    string rs1 = check_and_convert(vtemp[1], Register_enco, is_error);
    output+=rs1;
    // cout << rs1;
    output+=check_and_convert(vtemp[0], opcode, is_error);
    if (is_error=="False") return output;
    else 
        {
            return "Error";
        }
}

int main()
{
    map<string, int> labels;
    
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

    //opening input file
    ifstream input_file;
    input_file.open("i.txt");
    if (!input_file.is_open()) {
        cout << "Error opening input file! " << endl;

    }

    //reading all data from input file and storing it in full_program
    string line;
    vector<vector<string>> full_program;
    vector<string> v;
    while (getline(input_file, line)) 
    {
        v.clear();
        if (line == "") 
        {
            continue;
        }

        // Creates the vector of different strings containing the Instruction and Registers
        string word = "";
        for (int it = 0; it < line.length(); it++) 
        {
            if (line[it] == ' ' || line[it] == ',' || line[it] == '(' || line[it] == ')') 
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
            }
        }
        if (word != "") 
        {
            v.push_back(word);
            word = "";
        }

        full_program.emplace_back(v);
    }
    input_file.close();





    //check and convert the input to binary
    string temp_label = "";
    vector<string> binary_output;
    bool faulty_code = false;
    string temp_binary;
    int PC = 0;           //program counter
    
    for (int j = 0; j<full_program.size(); j++)
    {
        //R type when no label is present before
        if(ins_type[full_program[j][0]]=='R')
        {
            temp_binary = Rtype_to_binary(full_program[j], opcode, Register_enco, funct3, funct7);
            if (temp_binary=="Error")
            {
                faulty_code = true;
                break;
            }
            binary_output.emplace_back(temp_binary);
            PC++;
        }
        
        //when label is present before R type
        else if(ins_type[full_program[j][1]]=='R')
        {
            temp_label = full_program[j][0];
            if (temp_label[temp_label.length()-1] != ':')
            {
                faulty_code = true;
                break;
            }
            temp_label = temp_label.substr(0,temp_label.length()-1);
            labels.emplace(temp_label, PC*4);
            full_program[j].erase(full_program[j].begin());

            temp_binary = Rtype_to_binary(full_program[j], opcode, Register_enco, funct3, funct7);
            if (temp_binary=="Error")
            {
                faulty_code = true;
                break;
            }
            binary_output.emplace_back(temp_binary);
            PC++;
        }
        


        
        //S type when no label is present before
        else if(ins_type[full_program[j][0]]=='S')
        {
            temp_binary = Stype_to_binary(full_program[j], opcode, Register_enco, funct3);
            if (temp_binary=="Error")
            {
                faulty_code = true;
                break;
            }
            binary_output.emplace_back(temp_binary);
            PC++;
        }

        //when label is present before S type
        else if(ins_type[full_program[j][1]]=='S')
        {
            temp_label = full_program[j][0];
            if (temp_label[temp_label.length()-1] != ':')
            {
                faulty_code = true;
                break;
            }
            temp_label = temp_label.substr(0,temp_label.length()-1);
            labels.emplace(temp_label, PC*4);
            full_program[j].erase(full_program[j].begin());

            temp_binary = Stype_to_binary(full_program[j], opcode, Register_enco, funct3);
            if (temp_binary=="Error")
            {
                faulty_code = true;
                break;
            }
            binary_output.emplace_back(temp_binary);
            PC++;
        }

        
        
        
        
        //U type when no label is present before
        else if(ins_type[full_program[j][0]]=='U')
        {
            temp_binary = Utype_to_binary(full_program[j], opcode, Register_enco);
            if (temp_binary=="Error")
            {
                faulty_code = true;
                break;
            }
            binary_output.emplace_back(temp_binary);
            PC++;
        }
        
        //when label is present before U type
        else if(ins_type[full_program[j][1]]=='U')
        {
            temp_label = full_program[j][0];
            if (temp_label[temp_label.length()-1] != ':')
            {
                faulty_code = true;
                break;
            }
            temp_label = temp_label.substr(0,temp_label.length()-1);
            labels.emplace(temp_label, PC*4);
            full_program[j].erase(full_program[j].begin());

            temp_binary = Utype_to_binary(full_program[j], opcode, Register_enco);
            if (temp_binary=="Error")
            {
                faulty_code = true;
                break;
            }
            binary_output.emplace_back(temp_binary);
            PC++;
        }


        else
        {
            faulty_code = true;
            break;
        }
    }


    //if code is faulty, will give error else write the output to file
    if (faulty_code==true)
    {
        cout << "Error in line " << PC << endl;
    }
    
    else
    {
        ofstream output_file;
        output_file.open("Output.txt");
        if (!output_file.is_open()) {
            cout << "Error opening output file!" << endl;
        }

        for (int k = 0; k<binary_output.size(); k++)
        {
            output_file << binary_output[k] << endl;
        }

        output_file.close();
    }
}