#include "SendData.hpp"

#include <boost/algorithm/string.hpp>

/*Need to extract
  RA/Dec(J200)
  RA/Dec
  Ha/dec
  Az/Alt
*/

SendData::SendData(/* args */)
{
	stop = false; // check if the application is running or not
	// to start the thread
	// this->start();
}

SendData::~SendData()
{
	stop = true;
}

void SendData::setHTML_data(string data)
{

	// check if writable
	if (write_is_safe)
	{
		this->html_data = data; // write data
		is_obj_selected = true; // user select an object
	}
}

void SendData::run()
{
	unsigned int loop_counter = 0;
	while (!stop)
	{
		if (is_obj_selected)
		{
			writeData();
		}
		loop_counter++;
		write_is_safe = true;
		is_obj_selected = false;
		msleep(50);
	}
}

void SendData::writeData()
{
	write_is_safe = false; // not safe to write
	static int i = 0;
	i++;
	// cleanup data
	int start = str_find(html_data, ">");
	int end = str_find(html_data, "</fon");
	if (start == -1 || end == -1) // if not found then return
		return;
	start++; // increase start to start from next char
	string data = html_data.substr(start, end - start);
	data = str_replaceAll(data, "<h2>", "");	   // remove all <h2> tag
	data = str_replaceAll(data, "</h2>", "");	  // remove all </h2> tag
	data = str_replaceAll(data, "<br />", "<br>"); // replace all <br /> with <br>
	data = str_replaceAll(data, "<b>", "");		   // remove <b>
	data = str_replaceAll(data, "</b>", "");	   // remove </b>

	for (int i = 0; i < 30; i++)
		cout << endl;

    data = str_findWithName_excludeName(data, "RA/Dec (J2000.0):");
    start = data.find("/");
    float RA = getRA(data.substr(0, start));
    start++;
    float DEC = getDEC(data.substr(start, data.length()-start-1));
    cout << RA << endl;
    cout << DEC << endl;

}

// to find position in a string
int SendData::str_find(string str, string s)
{
	int length = str.length();
	int pos = str.find(s);
	return pos < length ? pos : -1;
}

// replace all substring with another substring
string SendData::str_replaceAll(string data, string str, string rep)
{

	int pos = 0;
	int l = str.length();
	while ((pos = data.find(str)) != -1)
	{
		data = data.replace(pos, l, rep);
	}
	return data;
}

// find string with name and return with name
string SendData::str_findWithName_containsName(string data, string str)
{
	int start = str_find(data, str);
	data = data.substr(start, data.substr(start).find("<br>"));
	return data;
}

// find string with name and return without name
string SendData::str_findWithName_excludeName(string data, string str)
{
	data = str_findWithName_containsName(data, str);
	data = str_replaceAll(data, str, ""); // remove name tag
	data = str_replaceAll(data, " ", ""); // replace all space
	return data;
}


// get RA value
float SendData::getRA(string data) {

    int flag = 1;
    string str_h = data.substr(0, data.find("h"));  // get h
    float h = stof(str_h);  // convert string to float
    if (h < 0)
        flag = -1;
    h *= flag;
    data = str_replaceAll(data, str_h+"h", ""); // remove hour
    string str_m = data.substr(0, data.find("m"));  // get m
    float m = stof(str_m);  // convert string to float
    data = str_replaceAll(data, str_m+"m", ""); // remove min
    float s = stof(data.substr(0, data.find("s"))); // get s
    return (h + m/60 + s/3600) * flag;   // calculate and return
}

// get dec value
float SendData::getDEC(string data) {
    int flag = 1;
    string str_deg = data.substr(0, data.find("°"));  // get deg(°)
    float deg = stof(str_deg);  // convert string to float
    if (deg < 0)
        flag = -1;
    deg *= flag;
    data = str_replaceAll(data, str_deg+"°", ""); // remove deg
    string str_m = data.substr(0, data.find("'"));  // get min(')
    float m = stof(str_m);  // convert string to float
    data = str_replaceAll(data, str_m+"'", ""); // remove min(')
    float s = stof(data.substr(0, data.find("\""))); // get sec(")
    return (deg + m/60 + s/3600) * flag;   // calculate and return
}












/************************************************************************/
// int casualDEC;
// int casualRA;
// void setup()
// {
// 	Serial.begin(9600);
// }
// String stringOne = "";
// void loop()
// {

// 	casualDEC = random(0, 90);
// 	casualRA = random(0, 24);
// 	String PROVA = (String)casualDEC;
// 	String PROVARA = (String)casualRA;
// 	if (Serial.available())
// 	{
// 		while (Serial.available() > 0)
// 		{
// 			char a = Serial.read(); // Stores current byte
// 			stringOne += String(a); // Append current Byte to message String
// 			delay(10);
// 		}
// 		if (stringOne == "#:GR#")
// 		{ // if command received = get RA do...
// 			Serial.print(PROVARA + ":00:00#");
// 		}
// 		if (stringOne == "#:GD#")
// 		{ // if command received = get DEC do...
// 			Serial.print("+" + PROVA + "*00#");
// 		}
// 		stringOne = "";
// 	}
// }