import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.Scanner;


public class scanner {

	String[] keywords={"break","case","char","const","continue","default","double","else","enum","extern",
			"float","for","goto","if","int","long","return","short","static","struct","switch","void","while"};
	String[] arithmetic={"+","-","*","/","%","++","--"};
	String[] relational={"==","!=",">","<",">=","<="};
	String[] punctuator={"{","}","(",")","[","]","=",",",".",";",":"};
	static FileInputStream fis;
	static char value;
	static String token;
	static int nextCharRead=0;
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		fis = new FileInputStream("file.txt");
		while(fis.available()>0){
			value=nextch();
			System.out.print(getnextToken());
		}
	}
	private static String getnextToken() {
		switch(value){
		case '/':
			char next=nextch();
			if(next=='/'){
				while(nextch()!='\n');
				return "\n";
			}
			else if(next=='*'){
				ignoreMultiLineComments();
			}
			else{
				nextCharRead=1;
				value=next;
				return "/";
			}
			break;
		default:
			return ""+value;
		}
		return "";
	}
	
	private static void ignoreMultiLineComments() {
		// TODO Auto-generated method stub
		char one=nextch(),two=nextch();
		while(one!='*' || two !='/'){
			one=two;two=nextch();
		}
	}
	private static char nextch() {
		if(nextCharRead==1){
			nextCharRead=0;
			return value;
		}
		try {
			return (char) fis.read();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return 0;
	} 
}
