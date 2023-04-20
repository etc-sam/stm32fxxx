/**
 * @brief array.c
 *
 * @param student: Sameer Almaldein
 * @param ID: 679699
 * @param University TU-Chemnitz
 * @param Master : ASE(Automotive Software Engineering )
 */ 

//********************************************************************************************
//
// include header files
//
//********************************************************************************************
#include "init.h"

//********************************************************************************************
//
// global variables' declarations 
//
//********************************************************************************************
//********************************************************************************************
//
// static variables' declarations 
//
//********************************************************************************************

//********************************************************************************************
//
//  static function ProtoType
//
//********************************************************************************************

//********************************************************************************************
//
//  static  functions' definitions
//
//********************************************************************************************
//********************************************************************************************
//
//  geniric buffer methods
//
//********************************************************************************************
/**
 * @brief get the first occurance of a key value in a buffer
 *			
 * @details get the first occurance of a key value in a buffer starting from
 *			from a specific index 																		
 * 
 * @param buf 			the buffer to look for 
 * @param len  			the length of the data buffer
 * @param val 			the key value to check for it
 * @param fromIndex 	the index to start the search from
 * @return int 
 * @retval -1: not found the key value within the buffer
 * @retval others: the index of the first occurance
 */
int mem_indexOf(void * buf, size_t len, int val, unsigned int fromIndex)
{
	if (fromIndex >= len) 
	  return -1;
	  
//	const char* temp =(const char*) memchr(buf + fromIndex,val,len);
	uint8_t* temp =(uint8_t*) memchr(buf + fromIndex,val,len);

	if (temp == NULL) 
	  return -1;
	return temp - (uint8_t*)buf;	   
}
//--------------------------------------------------------------------------------------------
/**
 * @brief 	get the last occurance of a key value in a buffer
 * 														
 * @details get the last occurance of a key value in a buffer starting from
 *			from a specific index 																		

 * @param buf 			the buffer to look for 
 * @param len  			the length of the data buffer
 * @param val 			the key value to check for it
 * @param fromIndex 	the index to start the search from
 * @return int 
 * @retval -1: not found the key value within the buffer
 * @retval others: the index of the first occurance
 */
int mem_lastindexOf(void * buf, size_t len, int val, unsigned int fromIndex)
{
	if (fromIndex >= len) 
	  return -1;
	  
	uint8_t* temp =(uint8_t*) memchr(buf + fromIndex,val,len);
	if (temp == NULL) 
	  return -1;
	return temp - (uint8_t*)buf;	  
}
//--------------------------------------------------------------------------------------------
/**
 * @brief  find a list of indecies of the key-value occurance in the buffer
 * 
 * @param buf 			the buffer to look for 
 * @param len  			the length of the data buffer
 * @param val 			the key value to check for it
 * @param ptr_list      indecies list for elements that match the key value 
 * @returns int         the length of the 
 * @retval the length of the 
 */
int mem_find_aslist(void * buf, size_t len, int val,uint8_t* ptr_list)//_aslist
{
   int fromindex=0;
   uint8_t i=0;
   while(fromindex!=-1) 
   {
	  fromindex=mem_indexOf(buf,len,val,fromindex);
	  if(fromindex!=-1)
	  {
	     ptr_list[i]=fromindex;
		 fromindex++;
		 i++;
	  }
   }
    return i;     	
}
//--------------------------------------------------------------------------------------------
/**
 * @brief 
 * 
 * @param buf 			the buffer to look for 
 * @param len  			the length of the data buffer
 * @param val 			the key value to check for it
 * @param ptr_list 
 * @return int 
 */
int mem_find_asArray(void * buf, size_t len, int val,array_t* ptr_list)//_asArray
{
   int fromindex=0,previndex=0;
   uint8_t i=0,start=0,end=0;
   while(fromindex!=-1) 
   {
	  fromindex=mem_indexOf(buf,len,val,fromindex);
	  if(fromindex!=-1)
	  {
		if(i>0) ptr_list[i-1].len=fromindex-previndex; 
	     ptr_list[i].ptr=(uint8_t *)(buf+fromindex);
		 previndex=fromindex;
		 fromindex++;
		 i++;
	  }
   }
   if(i>0)
   {
	 ptr_list[i-1].len=0;
     start=(uint8_t*)ptr_list[i-1].ptr-(uint8_t*)buf;
     end=mem_indexOf(buf,len,' ',start);
	 if(end !=-1)
	 {
       end=mem_indexOf(buf,len,' ',end+1);
	   if(end!=-1)
       {	
		len=end-start;	
	 	 ptr_list[i-1].len=len;
	   }
	 }
   }
   return i;     	
}
//---------------------------------------------------------------------------------------------
/**
 * @brief split the received command string to its parts 
 * 
 * @details split the command string from the whole message
 * 		    and builds up the different parts of the command struct
 * 			i.e. the command , parameters , and the values
 * 			as separated pointers to these strings.
 *  			
 * @param buf 	a pointer to the whole received message on the uart
 * @param len  	defines the length of the received message on the uart
 * @param val	check the searched key to split the message based on it
 * @param cmd 	a pointer to a command struct that builds the different part of the command
 * @return int 
 * @returns a parameter string length 
 */
int cmd_split(void * buf, size_t len, int val,cmd_t* cmd)
{
 unsigned int start=0,end=0;
 cmd->param_len=mem_find_asArray(buf,len,val,cmd->parameters);
 //cmd->msg.ptr=0;
 //cmd->msg.len=0;

 if(cmd->param_len>0)
 {	 
    start= cmd->parameters[cmd->param_len-1].ptr- (uint8_t*)buf;
	start+= cmd->parameters[cmd->param_len-1].len+1;
 }
 /*end=mem_indexOf(buf,len,' ',start);
 if(end!=-1)
 {
   cmd->msg.len=end-start;
   cmd->msg.ptr=(uint8_t*)(buf+start);  
 }
*/
 return cmd->param_len;
}
//---------------------------------------------------------------------------------------------
/**
 * @brief splits the parameter string to parameter-value pairs
 * 
 * @details splits the parameter string to parameter-value pairs
 * 
 * @param parameter  it is the parameter-value string array
 * @param ptr_param  it a struct the spilt the paratmeter string to param-value pairs 
 * @return int 
 */
int param_split(array_t parameter,  param_t * ptr_param)
{

 int par_start=0,par_end=0,data_end=0;
 uint8_t par_len=0,data_len=0;
 ptr_param->param=0;
 ptr_param->param_len=0;
 ptr_param->data=0;
 ptr_param->data_len=0;

 par_start=mem_indexOf(parameter.ptr,parameter.len,'-',0); 
 par_end=  mem_indexOf(parameter.ptr,parameter.len,' ',0);

 if(par_start !=-1 && par_end!=-1)
 {
	par_len=par_end-par_start;
	
	ptr_param->param=(uint8_t*)(parameter.ptr+par_start);
	ptr_param->param_len=par_len;
  if(parameter.len>par_end)
   {
	data_len=parameter.len-par_end-1;
	ptr_param->data=(uint8_t*)(parameter.ptr+par_end+1);
	ptr_param->data_len=data_len;
   }
 }
 return par_len ;//data_len;
}
//---------------------------------------------------------------------------------------------

