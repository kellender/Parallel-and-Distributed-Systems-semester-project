#include <mutex>
#include <sys/types.h>
#include <sys/stat.h>  //the power of the file system!!!!!
#include <unistd.h>
#include <thread>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdio.h>       // perror, snprintf
#include <stdlib.h>      // exit
#include <unistd.h>      // close, write
#include <string.h>      // strlen
#include <strings.h>     // bzero
#include <time.h>        // time, ctime
#include <sys/socket.h>  // socket, AF_INET, SOCK_STREAM,
// bind, listen, accept
#include <netinet/in.h>  // servaddr, INADDR_ANY, htons
using namespace std;
#define	MAXLINE		4096	// max text line length
#define	BUFFSIZE	8192    // buffer size for reads and writes
#define  SA struct sockaddr
#define	LISTENQ		1024	// 2nd argument to listen()
#define PORT_NUM        13002
#define MY_MASK 0777


//this will be a multicasted system, with replicated FS
//The file system will use the Active replication, where execution[-wx] are multicasted 
//And Argements[r--] are unicasted, read from the masterFS and hard coded with replicaManager[0] because all replica manages should have same state due to Active replication


//phases of an Active Replication system
//1)Request- FE attaches a unique id, totally ordered multicast to RMs.
//2)Coordination - delivers requests to all the RMs in the same (total) order.
//3) Execution- every RM executes the request. 
//4) Agreement-no agreement
//5) Response- front ends collect responses from RMs it gives the client the first response.


const string masterFS = "Users", replicaOne = "UsersR1", replicaTwo = "UsersR2";

class Connection{
public:
	Connection(int* connection): connfd(connection){
		fprintf(stderr," Inside thread heres the buffer:%s\n",buff);
		replicaManager.push_back(masterFS);
		replicaManager.push_back(replicaOne);
		replicaManager.push_back(replicaTwo);
	}


	void delUser(const string& information, const string& rm){ 
		mut.lock();
		vector<string> theFile;
		istringstream iss(information);
		string trash, usrfile = rm +"/Users.txt", line, username, passoword, cred, directory;
		iss >> trash >> username >> passoword;
		cred = username + " " +passoword;


		ifstream ifs(usrfile.c_str());
		if(!ifs){perror("Unable to open file");}
		while (getline(ifs, line)){
			if(line != cred){
				theFile.push_back(line);
			}		
		}
		ifs.close();
		ofstream ofs (usrfile.c_str(), std::ios::out | std::ios::trunc);
		if(!ofs){perror("Unable to open file");}
		for(size_t i(0); i < theFile.size(); ++i){
			ofs << theFile[i];
			ofs << "\n";
		}
		ofs.close();
		mut.unlock();
	}

	void rmFollower(const string& information, const string& rm){
		mut.lock();
		vector<string> theFile, followedByVec;
		istringstream iss(information);
		string trash,line, username, follower, usrfile;
		iss >> trash >> username >> trash >> follower;

		//current users following options	
		usrfile = rm +"/"+ username + "/following.txt";
		ifstream ifs(usrfile.c_str());
		if(!ifs){perror("Unable to open file");}
		while (getline(ifs, line)){
			if(line != follower){ //removes all instances of a follower!!!
				theFile.push_back(line);
			}		
		}
		ifs.close();
		ofstream ofs (usrfile.c_str(), std::ios::out | std::ios::trunc);
		if(!ofs){perror("Unable to open file");}
		for(size_t i(0); i < theFile.size(); ++i){
			ofs << theFile[i];
			ofs << "\n";
		}
		ofs.close();

		//user that is being followed
		string followedBy = rm + "/" + follower + "/folloedBY.txt";
		ifstream general(followedBy.c_str());//only because generals lead
		if(!general){perror("Unable to open file");}
		while (getline(general, line)){
			if(line != username){ //should remove all instances of a follower!!!
			followedByVec.push_back(line);
			}		
		}
		general.close();
		ofstream leader(followedBy.c_str(), std::ios::out | std::ios::trunc);
		if(!leader){perror("Unable to open file");}
		for(size_t i(0); i < followedByVec.size(); ++i){
			leader << followedByVec[i];
			leader << "\n";
		}
		leader.close();
		mut.unlock();
	}

	string viewFolloMsg(const string& information){
		mut.lock();
		istringstream iss(information);
		string trash, usrfile, followername, line, Followerfilename, msgs, username;
		iss >> trash >> username >> trash >> followername;
		string Convo = replicaManager[0] + "/" + username + "/message_with_" + followername + ".txt";

		string file = replicaManager[0] + "/" + username + "/following.txt";
		ifstream ifs(file.c_str());
		if(!ifs){perror("Unable to open file");}

		while(getline(ifs,line)){
		if(line == followername){
			ifstream cfs(Convo.c_str());
			if(!cfs){perror("Unable to open file");}
			while (getline(cfs, line)){
			msgs += line;
			msgs += "\n";
			}
			cfs.close();	
			ifs.close();
			mut.unlock();
			return msgs;
			}
		}
		return "0"; //failed
	}

	void addUser(const string& information, const string& rm){
		mut.lock();
		istringstream iss(information);
		string trash, user, password;
		iss >> trash >> user >> password;
		string directory = rm + "/" + user;

		int temp;
		printf("Default mask: %o\n", MY_MASK & ~022 & MY_MASK);
		temp = umask(0);
		printf("Previous umask = %o\n", temp);
		if ((temp = mkdir(directory.c_str(), MY_MASK)) != 0) {
			perror("ERROR: unable to mkdir\n");
			return; // user already exists or it failed to create a dir....!!!!
		}
		ofstream ofs;
		string fileName = rm + "/Users.txt";
		ofs.open(fileName.c_str(), std::ios::app);
		if(!ofs){perror("Unable to open file");}
		ofs << user << " " << password;
		ofs << "\n";
		ofs.close();
		fprintf(stderr, "yay\n");
		mut.unlock();
	}

	string saveMsg(const string& information, const string& rm){
		mut.lock();
		istringstream iss(information);
		string trash, file, username, follower, userFile, followerFile, line;
		iss >> trash >> username >> trash >> follower;
		//check if following
		file = rm + "/" + username + "/following.txt";
		ifstream ifs(file.c_str());
		if(!ifs){perror("Unable to open file");}
		while(getline(ifs,line)){
			if(line == follower){
				//to write messages in individual users message dir!
				userFile = rm + "/" + username + "/message_with_" + follower + ".txt";
				followerFile = rm + "/" + follower + "/message_with_" + username + ".txt";
				string msg, tmp;

				while(iss >> tmp){msg += tmp; msg += " ";};
				ofstream ofsUser, ofsFollower;
				ofsUser.open(userFile.c_str(), std::ios::app);
				if(!ofsUser){perror("Unable to open file");}
				ofsFollower.open(followerFile.c_str(), std::ios::app);
				if(!ofsFollower){perror("Unable to open file");}
				ofsUser << msg;
				ofsFollower << msg;
				ofsUser << "\n";
				ofsFollower << "\n";
				ofsUser.close();
				ofsFollower.close();
				mut.unlock();
				return "2"; //meaning dont send anything to the client [the php]

			}
		}
		return "0"; //failed
	}

	void addFollower(const string& information, const string& rm ){
		mut.lock();
		istringstream iss(information);
		string trash, file, follower, username, line;
		iss >> trash >> username >> trash >> follower;
		file = rm + "/" + username + "/following.txt";
		string followedBy = rm + "/" + follower + "/folloedBY.txt";		

		ifstream ifs(file.c_str());
		if(!ifs){perror("Unable to open file");}
		while(getline(ifs,line)){
			if(line == follower){
				ifs.close();
				fprintf(stderr, "folowing check\n");
				return; //dont do anything because the user is already in the list of folowers!!!
			}
		}
		ifs.close();

		ifstream general(followedBy.c_str());
		if(!general){perror("Unable to open file");}
		while(getline(general,line)){
			if(line == username){
				general.close();
				fprintf(stderr, "followBY check\n");
				return; //dont do anything because the user is already following another person
			}
		}
		general.close();

		string users =  rm + "/Users.txt", credentials;
		ifstream allUsers(users.c_str());
		while(getline(allUsers, credentials)){
			istringstream check(credentials);
			string existingUser;
			check >> existingUser;
			if(existingUser == follower){
				fprintf(stderr, "usercheck\n");
				allUsers.close();
				ofstream leader(followedBy.c_str(), std::ios::app); //named leader because that person is being foilowed by others...
				if(!leader){perror("Unable to open file");}

				ofstream ofs(file.c_str(), std::ios::app);
				if(!ofs){perror("Unable to open file");}
				leader << username << "\n";		
				ofs << follower;
				ofs << "\n";
				leader.close();
				ofs.close();
				mut.unlock();
				return;
			}
		}
		allUsers.close();
		return; //dont do anything if user dosent exist!
	}

	string checkLogin(const string& credientials){
		mut.lock();
		istringstream iss(credientials);
		string trash, cred, username, password;
		iss >> trash >> username >> password;
		cred = username + " " + password;
		ifstream ifs(replicaManager[0] + "/Users.txt"); //read are unicast! So i hardcoded it!
		if(!ifs){perror("Unable to open file");}
			string line;
		while (getline(ifs, line)){
			if(line == cred){
				ifs.close();
				mut.unlock();
				return "1";
			}
		}
		ifs.close();
		mut.unlock();
		return "0";
	}

	string combinestring(const string& information){
		mut.lock();
		istringstream iss(information);
		string state, cred;
		iss >> state >> cred;
		mut.unlock();
		if(state == "Cred"){ //read
		return checkLogin(information);
		}
		else if(state == "addFolo"){//write
		if(checkLogin(information) == "1"){ //user exists
		for(size_t i(0); i < replicaManager.size(); ++i){
		thread(&Connection::addFollower, this, information, replicaManager[i]).detach(); //makes for total ordering easier, where i can update all replica managers at the same time!!!!!
		}
		}
		}
		else if(state == "addMsg"){//write
		if(checkLogin(information) == "1"){ //user exists
		for(size_t i(0); i < replicaManager.size(); ++i){
		thread(&Connection::saveMsg, this, information, replicaManager[i]).detach(); 
		}
		}
		}
		else if(state == "newCred"){//write
		for(size_t i(0); i < replicaManager.size(); ++i){
		thread(&Connection::addUser, this, information, replicaManager[i]).detach();
		}
		fprintf(stderr, "post again check\n");
		}
		else if(state == "viewFolloMsg"){//read
		if(checkLogin(information) == "1"){ //user exists
		return viewFolloMsg(information);
		}
		return "0"; //return a fail
		}
		else if(state == "rmFollo"){//write
		if(checkLogin(information) == "1"){ //user exists
		for(size_t i(0); i < replicaManager.size(); ++i){
		thread(&Connection::rmFollower, this, information, replicaManager[i]).detach(); 
		}
		}
		}
		else if(state == "delUser"){//write
		if(checkLogin(information) == "1"){ //user exists
		for(size_t i(0); i < replicaManager.size(); ++i){
		thread(&Connection::delUser, this, information, replicaManager[i]).detach();
		}
		}
		}
		return "2";
	}

	void readConnection(){
		mut.lock();
		fprintf(stderr, "Connected\n");
		bzero(buff,strlen(buff));	//reset the buffer for the next read
		read(*connfd,buff,255);
		fprintf(stderr,"%s\n",buff);
		mut.unlock();
		string srvrMsg = combinestring(buff);
		mut.lock();
		char transmit[BUFFSIZE] = {};
		for (size_t i(0); i < srvrMsg.size(); ++i){
			transmit[i] = srvrMsg[i];
		}
		fprintf(stderr, "print write stuff  %s\n", transmit);
		if (transmit[0] != "2"){
			write(*connfd, transmit, strlen(transmit));
		}
		close(*connfd);
		fprintf(stderr, "Connection %d Closed!!!!!!!!\n", *connfd);
		mut.unlock();
	}

private:
	int* connfd;
	char buff[MAXLINE];
	mutable mutex mut;
	vector<string> replicaManager;
};

void makeDir(string dirName){
	int temp;
	printf("Default mask: %o\n", MY_MASK & ~022 & MY_MASK);
	temp = umask(0);
	printf("Previous umask = %o\n", temp);
	if ((temp = mkdir(dirName.c_str(), MY_MASK)) != 0) {
		perror("ERROR: unable to mkdir\n");
	}
}

int main(int argc, char **argv) {
	//create My FS if it dosent already exist!
	makeDir(masterFS);
	makeDir(replicaOne);
	makeDir(replicaTwo);

	//servers main purpose!!
	int	listenfd, connfd;
	struct sockaddr_in	servaddr;  

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Unable to create a socket");
		exit(1);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;

	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT_NUM);

	if (bind(listenfd, (SA *) &servaddr, sizeof(servaddr)) == -1) {
		perror("Unable to bind port");
		exit(2);
	}

	if (listen(listenfd, LISTENQ) == -1) {
		perror("Unable to listen");
		exit(3);
	}

	for ( ; ; ) {	
		perror("next");
		if ((connfd = accept(listenfd, (SA *) NULL, NULL)) == -1) {
			perror("accept failed");
			exit(4);
		}
		thread(&Connection::readConnection, new Connection(new int(connfd))).detach(); 
		std::this_thread::sleep_for (std::chrono::seconds(1));

	}
}
