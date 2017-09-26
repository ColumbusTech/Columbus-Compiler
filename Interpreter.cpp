#include <Interpreter.hpp>

namespace ColumbusCompiler
{

  C_Interpreter::C_Interpreter(int argc, char** argv)
  {
    if (argc != 3)
      return;

    mSrcFile = argv[1];
    mDstFile = argv[2];

    mInited = true;
  }

  bool C_Interpreter::load()
  {
    std::ifstream file;
    file.open(mSrcFile);

    if (!file.is_open())
    {
      file.close();
      return false;
    }

    std::string string;

    int i = 0;

    while(getline(file, string))
    {
      i++;
      std::stringstream ss(string);

      std::string line;

      while(ss >> line)
      {
        if (mTypes.size() > 0)
        {
          if (mTypes.back().type == 0)
            if (line[0] == ':')
              mTypes.back().endOperator = true;

          if (mTypes.back().type == 1)
            if (line[0] == '.')
              mTypes.back().endOperator = true;
        }

        if (line.compare(0, 5, "begin") == 0)
        {
          C_Type type;
          type.type = 0;
          type.str = i;
          type.line = line;

          if (line[line.size() - 1] == ':')
            type.endOperator = true;

          mTypes.push_back(type);
        } else if (line.compare(0, 3, "end") == 0)
        {
          C_Type type;
          type.type = 1;
          type.str = i;
          type.line = line;

          if (line[line.size() - 1] == '.')
            type.endOperator = true;

          mTypes.push_back(type);
        } else if (line.compare(0, 1, ":") != 0 || line.compare(0, 1, ".") != 0 || line.compare(0, 1, ";") != 1)
        {
          C_Type type;
          type.type = -1;
          type.str = i;
          type.line = line;

          if (line[line.size() - 1] == ':')
            type.endOperator = true;
          if (line[line.size() - 1] == '.')
            type.endOperator = true;
          if (line[line.size() - 1] == ';')
            type.endOperator = true;

          mTypes.push_back(type);
        }
      }
    }

    file.close();

    return true;
  }

  bool C_Interpreter::getErrors()
  {
    bool ret = true;

    for (size_t i = 0; i < mTypes.size(); i++)
    {
      if (mTypes[i].type == -1)
      {
        C_Error("%s: %i: Unknown type `%s`", mSrcFile.c_str(), mTypes[i].str, mTypes[i].line.c_str());
        ret = false;
      }

      if (mTypes[i].endOperator == false)
      {
        switch (mTypes[i].type)
        {
          case 0:
            C_Error("%s: %i: expected ':' `%s`", mSrcFile.c_str(), mTypes[i].str, mTypes[i].line.c_str());
            break;
          case 1:
            C_Error("%s: %i: expected '.' `%s`", mSrcFile.c_str(), mTypes[i].str, mTypes[i].line.c_str());
            break;
          default:
            C_Error("%s: %i: expected ';' `%s`", mSrcFile.c_str(), mTypes[i].str, mTypes[i].line.c_str());
            break;
        }
        ret = false;
      }
    }

    return ret;
  }

  void C_Interpreter::compile()
  {
    if (load() == false)
      return;

    if (getErrors() == false)
      return;
  }

  C_Interpreter::~C_Interpreter()
  {

  }

}
