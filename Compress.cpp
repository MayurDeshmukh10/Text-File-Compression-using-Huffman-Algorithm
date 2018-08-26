// C++ program for Huffman Coding
#include<cstring>
#include<vector>
#include<iostream>
#include<iomanip>
#include<queue>
#include<fstream>
using namespace std;
//int r = 0;
string str;
int q = 0;
int count3 = 0;
int count1 = 0;
string codes;
int num = 254;
char chh = char(num);
vector<pair<char,string> > charactermap;
vector<int> Huffcode;

//================================================================================================
class BitwiseWrite
{
	private:
	  char buf;
	  int Tbits;
	  ostream& out;
	public:


  BitwiseWrite(ostream & os) : out(os),buf(0),Tbits(0)
  {
 							//clear buffer and bit counter
  }

 
  void flush();   	 // write buffer into output file and clear it 
  void writeBit(int i);
};



void BitwiseWrite::flush() {
  out.put(buf);
  out.flush();
  buf = Tbits = 0;
}

void BitwiseWrite::writeBit(int i) // Write the least significant bit of the argument to the bit buffer
{
	if( i == -1)     //for last bit if buffer is not full still flush buffer
	{
		flush();
	}
  if(Tbits == 8) //if buffer full(8 bit) clear buffer
  {
    flush();
  }
  
  //if the int is 1, we must put the bit 1 into the buffer
  unsigned char mask = 1;
  if(i == 1) 
  {
    mask = mask << (7 - Tbits);
    buf = buf | mask;
  } 
  //if the int is 0, we must put the bit 0 into the buffer
  if(i == 0) 
  {
    mask = mask << (7 - Tbits);
    mask = ~mask;
    buf = buf & mask;
  } 
  Tbits++;                   //increment Tbits++
}
//===================================================================================================




struct MinHeapNode {

    // One of the input characters
    int data;

    // Frequency of the character
    int freq;

    // Left and right child
    MinHeapNode *left, *right;

    MinHeapNode(int data, int freq)
    {

        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};

// For comparison of
// two heap nodes (needed in min heap)
struct compare {

    bool operator()(MinHeapNode* l, MinHeapNode* r)

    {
        return (l->freq > r->freq);
    }
};

// Prints huffman codes from
// the root of Huffman Tree.
int p;
string str1= "";
int n=0;


void printCodes(struct MinHeapNode* root, string str)
{

    if (!root)
        return;

    if (root->data != chh)
    {
		char ch;
		ch = char(root->data);
        cout <<"\t    "<< ch << "\t\t\t  " << str << "\n";
	if(root->data == ' ')
	{
		codes = codes + "_" + " " + str + "Î";
	}
	else
		codes = codes + ch + " " + str + "Î";
	for(int i = 0;i < count3;i++)
	{

		if(charactermap[i].first == ch)
		{
			charactermap[i].second = str;
		}
  	 } 
     }
    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}
void printTree(ostream & out,struct MinHeapNode* root,int indent)
{
	if (root != NULL)
	{
		printTree(out, root->right, indent + 4);
		out << setw(indent) << " " << (char)root->data << endl;
		printTree(out, root->left, indent + 4);
	}
}
// The main function that builds a Huffman Tree and
// print codes by traversing the built Huffman Tree
priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;
void HuffmanCodes(int data[], int freq[], int size)
{
    struct MinHeapNode *left, *right, *top;

    // Create a min heap & inserts all characters of data[]


    for (int i = 0; i < size; ++i)                                //Build Heap
        minHeap.push(new MinHeapNode(data[i], freq[i]));

    // Iterate while size of heap doesn't become 1
    while (minHeap.size() != 1) {

        // Extract the two minimum
        // freq items from min heap
        left = minHeap.top();
        minHeap.pop();

        right = minHeap.top();
        minHeap.pop();

        // Create a new internal node with
        // frequency equal to the sum of the
        // two nodes frequencies. Make the
        // two extracted node as left and right children
        // of this new node. Add this node
        // to the min heap 'â– ' is a special value
        // for internal nodes, not used
        top = new MinHeapNode(chh, left->freq + right->freq);

        top->left = left;
        top->right = right;
        minHeap.push(top);
    }

    // Print Huffman codes using
    // the Huffman tree built above
    printCodes(minHeap.top(),"");
}
int total_bits_written()
{
	string temp;
	int total_bits = 0;
	for(int i=0; i < charactermap.size();i++)
	{
		temp = charactermap[i].second;
		for(int j=0; j < temp.length();j++)
		{
			total_bits++;
		}
	}
	return total_bits;
}


int ct = 0;
void cal_compressionRatio()
{
	long double csize = 0;
	long double size = 0;
	long double cratio;
	long long lsize = 0;
	long long lcsize = 0;
	char ch;
	int x;
	x = count3;
	x = x - 1;
	lsize = x;
	lcsize = Huffcode.size()/8;
	size = x * 8;
	size = size /8;
	cout<<"\nActual Size of File  = "<<lsize<<" Bytes";
	csize = Huffcode.size()/8;
	cout<<"\nSize of Compressed File = "<<lcsize<<" Bytes";
	cratio = (csize/size)*100;
	cout<<"\nCompression Ratio achieved : "<<cratio<<"% !";
}
void calculate_frequency(int frequency[],char filename[])
{
    char ch,ch1;
    int y;
    int f;
   int x;
    ifstream fin;
    fin.open(filename);
	if(!fin.is_open())
	{
		cout <<"Error !!! Cannot open Source file.\n";
		cin>>y;
		exit(1);
	}
    while(fin.get(ch))
    {
        
	if( ch >=32 && ch < 255)
	{
		charactermap.push_back(make_pair(ch,""));
		count3++;
	}
        y = int(ch);
        frequency[y]=frequency[y]+1;
    }
     ch1 = char(129);
    charactermap.push_back(make_pair(ch1,""));
    count3++;
    fin.close();
}

void write_codes()     //creates codes file
{
	ofstream out;
	out.open("codes.txt");
	for(int i=0; i < codes.size();i++)
	{
		if(codes[i] != 'Î')
		{
			out<<codes[i];
			
		}
		else
			out<<endl;
	}
	out.close();
} 

void SeperateCharacter(int frequency[],int actual_frequency[],int ASCII_values[])
{
	int k =0;
   	 int y=0;
   	 for(int j=32;j < 254;j++)   //For seperating occurring and non-occurring characters & to create actual 
   	 {			             // frequency array & ASCII_values array
		if(frequency[j] != 0)
        	{
          	  actual_frequency[k] = frequency[j];
           	 ASCII_values[y] = j;
           	 y++;
           	 k++;
           	 count1++;
		}
    	}

	actual_frequency[y] = 1;     // For adding pseudo-EOF in actual_frequency & ASCII_values arrays
	ASCII_values[k] = 129;
	count1++;
}

void Convert_StringBits_to_IntegerBits()
{
	string temp;
	for (int i = 0; i < charactermap.size();i++)
   	 {
		temp = charactermap[i].second;                   
		for(int j=0;j < temp.size();j++)          //For storing strings bits into integer vector,for 								   writing bit by bit in file 
		{
			if(temp[j] == '1')
			{
				Huffcode.push_back(1);
			}
			else
			{
				Huffcode.push_back(0);
			}
		}
     		//cout  <<"\t"<< charactermap[i].first <<"\t"<< charactermap[i].second<<"\n";
  	  }
	Huffcode.push_back(-1);
}
void printFrequencyTable(int actual_frequency[],int ASCII_values[])
{
	char ch;
	string str = "";
	str = str+"Space";
	cout<<"\n\tFrequency Table of Characters present in file\n\n";
	cout<<"\t===================================================\n";
	cout<<"\tCharacters\t\tFrequency\n";
	cout<<"\t===================================================\n";
	for(int i=0; i < count1; i++)
	{
		ch = char(ASCII_values[i]);
		if(ch == ' ')
			cout<<"\t    "<<str<<"\t\t  "<<actual_frequency[i]<<"\n";
		else	
			cout<<"\t    "<<ch<<"\t\t\t  "<<actual_frequency[i]<<"\n";
	}
}

// Driver program to test above functions
int main()
{
	int frequency[256];
	int ASCII_values[256];
	int actual_frequency[256];
	char ch;
	char filename[50];
	char cfilename[50];
	string decode;
	cout<<"\n\t====================================";
	cout<<"\n\t\t  Text File Compressor\n";
	cout<<"\t====================================";
	cout<<"\n\nEnter Name of File to Compress : ";
	cin>>filename;
	
   	for(int i=0;i < 255;i++)     //To set initial values of arrays
  	{
     		ASCII_values[i] = 0;
    	 	actual_frequency[i] = 0;
    	 	frequency[i] = 0;
   	}
   	calculate_frequency(frequency,filename);  	//To calculate frequency of each character in file
	
   	SeperateCharacter(frequency,actual_frequency,ASCII_values);  //Make actual frequency array and ASCII values
	
	printFrequencyTable(actual_frequency,ASCII_values);  // Print frequency table
	cout<<"\nCharacter Table with Huffman codes \n";
	cout<<"\n\tCharacter\t\tHuffman Code\n";
	
   	HuffmanCodes(ASCII_values,actual_frequency,count1);  //Function to build Huffman tree

	Convert_StringBits_to_IntegerBits();          //Converts character from charactermap to int vector
	
	int len = strlen(filename);
	filename[len-1] = 'p';
	filename[len-2] = 'm';
	filename[len-3] = 'c';
	cout<<"\n";
	cout<<"\nHuffman encoding Tree : \n";
	printTree(cout,minHeap.top(),0);      //To display formed Tree  with 'â– ' as parent nodes(including root)
	write_codes();
	ofstream fout;
  	fout.open(filename,ios::binary);

	cal_compressionRatio();                //To calculate compression ratio
	int temp1;
	BitwiseWrite s(fout);
	cout<<"\nProcessing.... Plz wait !!!";
	for(int d = 0;d < Huffcode.size();d++) {
	    temp1 = Huffcode[d];
	    s.writeBit(temp1);                //To write Bit by bit by bit in compressed file
	  }
	cout<<"\nCompression Successful !!!";
	int v;
	cout<<"\nEnter any key to exit : ";
	cin>>v;
    	return 0;

}
