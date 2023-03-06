/**
 * @brief ARRAY.h
 *
 * @param student: Sameer Almaldein
 * @param ID: 679699
 * @param University TU-Chemnitz
 * @param Master : ASE(Automotive Software Engineering )
 */ 


#ifndef _ARRAY_H_
#define _ARRAY_H_

//********************************************************************************************
//
//  geniric structs
//
//********************************************************************************************
/**
 * @brief an array of bytes structs
 * 
 * @param ptr a pointer to an array of bytes (the first location index)
 * @param len the length of the array of bytes
 */
typedef struct _array_t
{
 uint8_t * ptr; //! a pointer to an array of bytes (the first location index)
 uint8_t len;   //! the length of the array of bytes
}array_t;

/**
 * @brief parameter struct 
 * 
 * @param param     a pointer to array of parameter string 
   @param param_len the length of the parameter string
 * @param data      a pointer to the values  
 * @param data_len  the length of the values string

 */

typedef struct _param_t
{
 uint8_t * param;   //! a pointer to array of parameter string
 uint8_t param_len; //!the length of the parameter string

 uint8_t * data;    //! a pointer to the values
 uint8_t data_len;  //! the length of the values string

}param_t;

/**
 * @brief a command structus that would be received on the uart
 * 
 * @details a command has a value and up to six parameters where each parameter is 
 *      a pointer to a string, also the command consists of a number of parameter values
 *      which are defined by the msg field
 * @param  cmd          a command value 
 * @param param_len     defines the parameters array length
 * @param parameters    up to six paramtere a command may have   
*  @param msg           the data portion of the command

 */
typedef struct _cmd_t
{
   uint8_t cmd;                 //! a command value 
   uint8_t param_len;           //! defines the parameters array length
   array_t parameters[6];       //! up to six paramtere a command may have   
   array_t msg;                 //! the data portion of the command
}cmd_t;


//********************************************************************************************
//
//  geniric Array methods
//
//********************************************************************************************
//! give the first index of a specific character in the array buf
extern int mem_indexOf(void * buf, size_t len, int val, unsigned int fromIndex);
//! give the last index of a specific character in the array buf
extern int mem_lastindexOf(void * buf, size_t len, int val, unsigned int fromIndex);

//! give the first index of a specific values array in the array buf
extern int mem_find_aslist(void * buf, size_t len, int val,uint8_t* ptr_list);//_aslist
//! give the last index of a specific values array in the array buf
extern int mem_find_asArray(void * buf, size_t len, int val,array_t* ptr_list);//_asArray

//********************************************************************************************
//
//  geniric command and parameter  methods
//
//********************************************************************************************
//! split the parameter string to parameter-value pairs
extern int param_split(array_t parameter,  param_t * param);
//! split the command string from the whole message
extern int cmd_split(void * buf, size_t len, int val,cmd_t* cmd);

//********************************************************************************************
//
//  
//
//********************************************************************************************


#endif /* _ARRAY_H_ */