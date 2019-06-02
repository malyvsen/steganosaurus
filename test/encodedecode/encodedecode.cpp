#include "../catch.hpp"
#include "../../steganosaurus/_include.hpp"

void encode(std::string dataPath, std::string carrierPath, std::string outputPath)
{
    std::ifstream photo;
    photo.open(carrierPath,std::ios_base::in | std::ios_base::binary);
    std::ifstream data;
    data.open(dataPath,std::ios_base::in | std::ios_base::binary);
    std::ofstream output;
    output.open(outputPath,std::ios_base::out | std::ios_base::binary);
    SimpleEncoder obj;
    obj.Encode(photo, data, output);
    photo.close();data.close();output.close();
}
void decode(std::string carrierPath, std::string outputPath)
{
    std::ifstream photo;
    photo.open(carrierPath,std::ios_base::in | std::ios_base::binary);
    std::ofstream output;
    output.open(outputPath,std::ios_base::out | std::ios_base::binary);
    SimpleEncoder obj;
    obj.Decode(photo, output);
    photo.close();output.close();
}
bool checkfile(std::string pathA, std::string str)
{
    std::ifstream ifs (pathA);
    std::string strFromFile;
    if(ifs.tellg()==0 && str.length()==0) throw 2137;
    std::getline (ifs, strFromFile, (char) ifs.eof());
    ifs.close();
    if(strFromFile.length()!= str.length()) return false;
    for(int i=0; i < str.length() ; i++) if(str[i]!=strFromFile[i])return false;

    return true;
}

SCENARIO("encodeDecode", "[encode-decode]")
{
    std::string strData0="encodedecode/data/data-0.txt";
    std::string strData80="encodedecode/data/data-80.txt";
    std::string strData210="encodedecode/data/data-210.txt";
    std::string strData862="encodedecode/data/data-862.txt";
    std::string strData155000 = "encodedecode/data/data-155.000.txt";
    std::string strImg1508="encodedecode/data/img-1.508.jpg";
    std::string strImg13="encodedecode/data/img-12.917.jpg";
    std::string strImgBlank1655="encodedecode/data/img-blank-1.655.jpg";
    std::string strImgblank679="encodedecode/data/img-blank-679.jpg";
    std::string strImg155000 = "encodedecode/data/img-155.000.jpg";
    std::string str80="C++ is standardized by the International Organization for Standardization (ISO),";
    std::string str210=std::string("C++ is standardized by the International Organization for Standardization (ISO),")+
    " with the latest standard version ratified and published by ISO in December 2017 as ISO/IEC 14882:2017 (informally known as C++17)";
    std::string str862= std::string("C++ is standardized by the International Organization for Standardization (ISO), with the latest standard version")+
    std::string(" ratified and published by ISO in December 2017 as ISO/IEC 14882:2017 (informally known as C++17).[9] The C++ programming language was ")+
    std::string("initially standardized in 1998 as ISO/IEC 14882:1998, which was then amended by the C++03, C++11 and C++14 standards. The current C++17 standard")+
    std::string(" supersedes these with new features and an enlarged standard library. Before the initial standardization in 1998, C++ was developed by Danish computer")+
    std::string(" scientist Bjarne Stroustrup at Bell Labs since 1979 as an extension of the C language; he wanted an efficient and flexible language similar to C that also")+
    std::string(" provided high-level features for program organization.[10] C++20 is the next planned standard, keeping with the current trend of a new version every three years[11]");

   GIVEN("normal_Ratio 0.6%")
   {
       encode(strData80,strImg13,"encodedecode/data/output/output1.jpg");
       decode("encodedecode/data/output/output1.jpg" , "encodedecode/data/output/output1.txt"  );
       REQUIRE(checkfile("encodedecode/data/output/output1.txt", str80));
   }
   GIVEN("normal_Ratio 1%")
   {
       encode(strData210,strImg13,"encodedecode/data/output/output2.jpg");
       decode("encodedecode/data/output/output2.jpg" , "encodedecode/data/output/output2.txt"  );
       REQUIRE(checkfile("encodedecode/data/output/output2.txt", str210));
   }

   GIVEN("normal_Ratio 6%")
   {
       encode(strData862,strImg13,"encodedecode/data/output/output3.jpg");
       decode("encodedecode/data/output/output3.jpg" , "encodedecode/data/output/output3.txt"  );
       REQUIRE(checkfile("encodedecode/data/output/output3.txt", str862));
   }

   GIVEN("normal_Ratio 57%")
   {
       encode(strData862,strImg1508,"encodedecode/data/output/output4.jpg");
       decode("encodedecode/data/output/output4.jpg" , "encodedecode/data/output/output4.txt"  );
       REQUIRE(checkfile("encodedecode/data/output/output4.txt", str862));
   }

   GIVEN("blank_Ratio 5%")
   {
       encode(strData80,strImgBlank1655,"encodedecode/data/output/output5.jpg");
       decode("encodedecode/data/output/output5.jpg" , "encodedecode/data/output/output5.txt"  );
       REQUIRE(checkfile("encodedecode/data/output/output5.txt", str80));
   }

   GIVEN("blank_Ratio 100%")
   {
       encode(strData862,strImgblank679,"encodedecode/data/output/output6.jpg");
       decode("encodedecode/data/output/output6.jpg" , "encodedecode/data/output/output6.txt"  );
       REQUIRE(checkfile("encodedecode/data/output/output6.txt", str862));
   }
}

SCENARIO("encodeDecodeManualChecking", "[encode-decode-manual-checking]")
{
    std::string strData155000 = "encodedecode/data/data-155.000.txt";
    std::string strImg155000 = "encodedecode/data/img-155.000.jpg";
   GIVEN("Dino_Ratio 100%")
   {
       encode(strData155000,strImg155000,"encodedecode/data/output/output7.jpg");
       decode("encodedecode/data/output/output7.jpg" , "encodedecode/data/output/output7JPG.jpg"  );
   }
}



