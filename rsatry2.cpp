#include "RSA.h"
#include "BigInt.h"
#include "stdlib.h"
#include <cmath>
#include<iostream>
#define RAND_LIMIT32 0x7FFFFFFF
using namespace RSAUtil;

int main(int argc, char*argv[]){      /*********************************************************
 * A Simple Driver
 * *******************************************************
 */
        unsigned long int *a;
        unsigned long int arr[10];
        a=&arr[0];
	unsigned long int *b;
        unsigned long int brr[10];
        b=&brr[0];
	unsigned long int *c;
        unsigned long int crr[10];
        c=&crr[0];
	unsigned long int *d;
        unsigned long int drr[10];
        d=&drr[0];
	BigInt message, result, cipher, deciphered, random, value, value2;
        BigInt pubkey, privatekey;
        BigInt gnm, encrypt, decrypt, check;

      //  RSA myRSA;  // default , no args, program generates its own p and q
      RSA myRSA(102563,102841);
     RSA newrsa;
//	RSA myRSA = new RSA(11,13);// doesnt execute, because the size of N is less than 16 bits


       pubkey= myRSA.getPublicKey();
       privatekey = myRSA.getPrivateKey();
       std::cout<<"Public Key Of Bob obtained by Alice  : ";
       pubkey.toULong(a,4);
       std::cout<<*a<<std::endl;

       privatekey.toULong(b,4);
       std::cout<<"Private Key of Bob		        : "<<*b<<std::endl;

	

      gnm = myRSA.getModulus();
       std::cout<<"N shared to Alice 			: "<<gnm.toHexString()<<std::endl;
	message = 1000;
	std::cout<<"Message in Hex Format		: "<<message.toHexString()<<std::endl;
	message.toULong(a,4);
	std::cout<<"Message ordinary			: "<<*a<<std::endl;
        random= int(((double)rand()/RAND_MAX)*RAND_LIMIT32);
	std::cout<<"Random number in Hex Format		: "<<random.toHexString()<<std::endl;
	random.toULong(a,4);
	std::cout<<"Random number ordinary		: "<<*a<<std::endl;
	encrypt = modPow(random,pubkey,gnm);
	std::cout<<"Encrypted random number in Hex Format: "<<encrypt.toHexString()<<std::endl;
	encrypt.toULong(c,4);
	std::cout<<"Encrypted random number ordinary	: "<<*c<<std::endl;
	message = message*encrypt;
	message.toULong(c,4);
	std::cout<<"message * random number 		: "<<*c<<std::endl;
	result = (message % gnm);
	std::cout<<"Blob to Bob from Alice Hex Format	: "<<result.toHexString()<<std::endl;	
	result.toULong(d,4);
	std::cout<<"Blob to Bob from Alice ordinary	: "<<*d<<std::endl;
	decrypt = modPow(result,privatekey,gnm);
	std::cout<<"Decryted message by Bob Hex Format	: "<<decrypt.toHexString()<<std::endl;
	decrypt.toULong(b,4);
	std::cout<<"Decrypted by Bob ordinary		: "<<*b<<std::endl;
	value2 = decrypt / random;
	std::cout<<"Alice divides the message from Bob by random number in step 1 Hex	   : "<<value2.toHexString()<<std::endl;
	value2.toULong(b,4);
	std::cout<<"Alice divides the message from Bob by random number in step 1 Ordinary :"<<*b<<std::endl;
	value2 = value2 % gnm;
	std::cout<<"Alice takes % N for signed message Hex: "<<decrypt.toHexString()<<std::endl;
	decrypt.toULong(c,4);
	std::cout<<"Alice takes % N for signed message Ordinary: "<<*c<<std::endl;
	value = modPow(message,privatekey,gnm); 
	value.toULong(d,4);
	std::cout<<"Verification by encrypting with Bob's pubkey Hex: "<<value.toHexString()<<std::endl;
	std::cout<<"Verification by encrypting with Bob's pubkey: "<<*d<<std::endl;

	/*std::cout<<"Original message is "<<message.toHexString()<<std::endl;
	message.toULong(a,4);
	std::cout<<"Original message is "<<*a<<std::endl;
	encrypt = modPow(message,pubkey,gnm);
	decrypt = modPow(encrypt,privatekey,gnm);
	encrypt.toULong(c,4);
	decrypt.toULong(d,4);
	std::cout<<"encryt "<<encrypt.toHexString()<<std::endl;
	std::cout<<"decrypt "<<decrypt.toHexString()<<std::endl;
	std::cout<<"encryt "<<*c<<std::endl;
	std::cout<<"decrypt "<<*d<<std::endl;*/

      /* newrsa.setN(gnm);
       newrsa.setPublicKey(myRSA.getPublicKey());
      gnm = newrsa.getModulus();
       std::cout<<"N  in new is"<<gnm.toHexString()<<std::endl;
       std::cout<<"Old Pub Key "<<pubkey.toHexString()<<std::endl;
       pubkey= newrsa.getPublicKey();
       std::cout<<"New Pub Key "<<pubkey.toHexString();*/

      /*
	std::cout<<(message^pubkey)%gnm.toHexString;
	std::cout<<(((message^pubkey)%gnm)^privatekey)%gnm.toHexString;*/
     //  message = int(((double)std::rand()/RAND_MAX)*RAND_LIMIT32);




/*     cipher = myRSA.encrypt(message);
       deciphered = myRSA.decrypt(cipher);

       std::cout<<"message: "<<message.toHexString()<<"\tcipher: "<<cipher.toHexString()<<"\tdeciphered: "<<deciphered.toHexString()<<std::endl;
*/
}

