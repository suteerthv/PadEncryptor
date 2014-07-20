
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<unistd.h>
#define null "\0"
using namespace std;
class PadEncryptor
	{
	private:
		string filename;
		string padname;
		string secret;
		ifstream is;
		
		int fsize;
		int filesize(string fn)
			{
			int a;
			is.open(fn.c_str(),ios::binary);
			is.seekg(0,ios::end);
			a = is.tellg();
			is.close();
			return a;
			}


	public:
		string text;
		

		void Encrypt()
			{
	

				int padsize=filesize(padname);
				fsize = text.length();	
				char* bufferText = new char [fsize];

				if(padsize < text.length())
							{
						cout << "Pad size:"<<padsize<<" Text Size:"<<text.length(); exit(1);
							}
		
					

				if(text==null){
						//the next series of commands puts text into text and secret
						fsize = filesize(filename);
					
						if(padsize < fsize)
							{
							cerr << "Pad file too small"<<padsize << fsize << endl;
							}				

	
						is.open(filename.c_str(),ios::binary);
					
						is.read(bufferText,fsize);	
						is.close();
						text = (string) bufferText;
						}
					
				is.open(padname.c_str(),ios::binary);
				
				//read from back	
					is.seekg(fsize,ios::beg);
					
					is.read(bufferText,fsize);
					
					secret=	(string)bufferText;	
					is.close();		
				//xor the plain text to cipher
					for(int i=0;i< fsize;i++)
						{
						text[i] ^= secret[i];
						}
					
					

				//remove the excess
					truncate(padname.c_str(),padsize-fsize);				
					cout<<text;
					}
				
			
					
			
		void getFilename(string fname)
			{
			filename = fname;
			}
		void getPadname(string pname)
			{
			padname = pname;
			}
		void getText()
			{
			cin >> text;
			}
		

	};

int main(int argc ,  char* argv[])
    {
	
    PadEncryptor enc;
    if(argc<2)
        {
        std::cout<<"Usage:"<<std::endl<<"\t"<<argv[0]<<"{input file} {pad file}"<<std::endl<<"\tpadencryptor {padfile}(and enter the text.)"<<endl;
      }
    if(argc == 2)
	{
	enc.getPadname(argv[1]);
	enc.getText();
	enc.Encrypt();
	}
    else if(argc ==3){
	enc.getFilename(argv[1]);
	enc.getPadname(argv[2]);
	enc.Encrypt();}
	return 1;
}
