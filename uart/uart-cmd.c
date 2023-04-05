/**
 * @brief uart-cmd.c
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
//! handles the parameter string to later use it during executing the command
//static void  uart_param_handle(uint8_t * param, size_t param_len);
//! execute the command string with both the parameters and values strings
//static void  uart_param_exeute(uint8_t * param, size_t param_len,uint8_t * data, size_t data_len);

//! handles the parameter string to for a spcific parameter 
static void  uart_param_handle(USART_TypeDef * usartx,uint8_t cmd,uint8_t * param, size_t param_len);
//! handles the parameter as an array_t type with command value 
static void  uart_param_array_handle(USART_TypeDef * usartx,uint8_t cmd,array_t param);

//! execute the command with both the parameters and values strings
static void  uart_cmd_param_exeute(USART_TypeDef * usartx,uint8_t cmd,uint8_t * param, size_t param_len,uint8_t * data, size_t data_len);


//! execute the command with both the parameter struct and a command value 
static void uart_param_exeute(USART_TypeDef * usartx,uint8_t cmd,param_t p);

//! handles the parameters value array of the tx command

//static uint8_t  uart_tx_param_handle(uint8_t * data, size_t data_len);
//! execute the tx command with the parameters value as a struct
//static uint8_t  uart_tx_param_execute(param_t p);

//********************************************************************************************
//
// uart command and frame handling definition
//
//********************************************************************************************
void  uart_param_handle(USART_TypeDef * usartx,uint8_t cmd,uint8_t * param, size_t param_len)
{
 int par_start=0,par_end=0,data_end=0;
 uint8_t par_len=0,data_len=0;
 uint8_t data_buf[10]={0};
 uint8_t par_buf[10]={0};
 char buf[16]="";

 par_start=mem_indexOf(param,param_len,'-',0); 
 par_end=  mem_indexOf(param,param_len,' ',0);
 
 if(par_start !=-1 && par_end!=-1)
 {
	par_len=par_end-par_start;
	data_len=param_len-par_end-1;

    memcpy((uint8_t*)par_buf, (uint8_t*)param+par_start,par_len);    	
	memcpy((uint8_t*)data_buf,(uint8_t*)param+par_end+1,data_len);
    /*
    // could print some extra data 
    uart_print("param:");
    uart_println((char *)par_buf);
    uart_print("data:");
    uart_println((char *)data_buf);
    */
    uart_cmd_param_exeute(usartx,cmd,par_buf,par_len,data_buf,data_len);
 }
 else
 {
    uart_println(usartx,"parameter is incorrect ....!");
    uart_print(usartx,"par_start:");
    itoa(par_start,buf,10);
    uart_println(usartx,(char *)buf);

    uart_print(usartx,"par_end:");
    itoa(par_end,buf,10);
    uart_println(usartx,(char *)buf);
 }

}
//--------------------------------------------------------------------------------------------------------------------------
/**
 * @brief  execute based on the cmd the specific parameter passed
 * @details           actually it is handle  until the TX command 
 *                    as other command does not use parameters
 * @param cmd         an uint8_t command id 
 * @param param       the parameter array it is a string
 * @param param_len   the parameter array length
 * @param data        the data array portion of these parameters, also it is a string
 * @param data_len    the length of the data array
 */
void uart_cmd_param_exeute(USART_TypeDef * usartx,uint8_t cmd,uint8_t * param, size_t param_len,uint8_t * data, size_t data_len)
{
  uint8_t val=0;
  char buf[16]="";
/*   
 switch(cmd) 
   {
      case _TX:
              src_address=-1;
              dst_address=-1;
             if(strcasecmp((const char *)param,"-s")==0)
             {
              	val=atol((const char *)data);              
              	src_address=val;   
              	uart_print(USART1,"\nsrc:");
              	itoa(src_address,buf,10);
              	uart_println(buf);
             }
            else if(strcasecmp((const char *)param,"-d")==0)
            {
              	val=atol((const char *)data);              
              	dst_address=val;               
              	uart_print(USART1,"\ndst:");
              	itoa(dst_address,buf,10);
              	uart_println(buf);
            }            
      break; 
   }  
 */
}
//--------------------------------------------------------------------------------------------------------------------------
/**
 * @brief handle the command parameters string 
 * @details   handle the command parameters string by spliting the paramters into two pairs
 *            here the parameter is defined as a struct of two portions
 *            one is the parameter id while the other is the parameter value
 * @param cmd   the command id
 * @param param the parameter array 
 */
void  uart_param_array_handle(USART_TypeDef * usartx,uint8_t cmd,array_t param)
{

 int len=0;
 char buf[16]="";
 param_t p={0};
 len=param_split(param,(param_t*)&p);

 if(len>0)
 {
    uart_param_exeute(usartx,cmd,p);
	//uart_param_exeute(cmd,p.param,p.param_len,p.data,p.data_len);
 }
 else
 {
    uart_println(usartx,"parameter is incorrect ....!");
 }

}
//--------------------------------------------------------------------------------------------------------------------------
/**
 * @brief a generic parameter execute method that 
 *        look to specific functions which had parameters
 * @details the commands with no parameter just shown and not handled because of break
 *          and using the defualt to specify the unrecognized command  
 * @param cmd the command ID
 * @param p   the parameter struct after spliting  
 */
void uart_param_exeute(USART_TypeDef * usartx,uint8_t cmd,param_t p)
{
   switch (cmd)
    {
//      case _MPU_STOP: 				break;
//      case _MPU_WHO_IAM: 			break;
//      case _MPU_INIT: 				break;
//      case _MPU_READ_ALL: 			break;
//      case _MPU_READ_ACCEL: 		break;
//      case _MPU_READ_GYRO: 			break;
//	    case _MPU_READ_TEMP: 			break;
//	    case _MPU_READ_REG:			break;
//	    case _MPU_WRITE_REG:			break;

      //case _TX: uart_tx_param_execute(p); break;
      //case _RX: break;
      default:
        	uart_println(usartx,"unknown command ....");
    }
}
//--------------------------------------------------------------------------------------------------------------------------


//********************************************************************************************
//
// uart command and frame handling definition
//
//********************************************************************************************
/**
 * @brief handles the whole message as if it is a correct command structure
 * @details handles the whole message received on the uart and check if it has a
 *          a correct structure command with paramters and values pairs
 *          However, in case of an incorrect command an error message 
 *          sends in response on the uart
 * @return void
 */
void uart_handle_frame(USART_TypeDef * usartx)
{
 int cmd_start,cmd_end,data_end;
 uint8_t cmd_len=0,data_len=0;
 uint8_t data_buf[32]={0};
 uint8_t cmd_buf[16]={0};
 char buf[16]="";
 
 cmd_start=mem_indexOf(rx_buffer,rx_buffer_length,'#',0);
 cmd_end=  mem_indexOf(rx_buffer,rx_buffer_length,' ',0);
 data_end= mem_indexOf(rx_buffer,rx_buffer_length,';',0);
 
 if(cmd_start !=-1 && cmd_end!=-1 && data_end!=-1)
 {
	cmd_len=cmd_end-cmd_start-1;
	data_len=data_end-cmd_end-1;
	data_len=(data_len>0)? data_len-1:0; 

     memcpy((uint8_t*)cmd_buf, (uint8_t*)rx_buffer+cmd_start+1,cmd_len);    	
	 memcpy((uint8_t*)data_buf,(uint8_t*)rx_buffer+cmd_end+1,data_len);
	 uart_handle_cmd(usartx,cmd_buf,cmd_len,data_buf,data_len);
	 uart_println(usartx,"");
 }
 else
 {
    uart_println(usartx,"command error....!");
	uart_print(usartx,"cmd_start:");
	utoa(cmd_start,buf,10);
	uart_println(usartx,buf);
	uart_print(usartx,"cmd_end:");
	utoa(cmd_end,buf,10);
	uart_println(usartx,buf);
	uart_print(usartx,"data_end:");
	utoa(data_end,buf,10);
	uart_println(usartx,buf);
 }

}
//------------------------------------------------------------------------------------------------------------
/**
 * @brief handle the correct structured received command message
 * 
 * @details this method gets two arrays one is a pointer to the command string while 
 *          the second part is a pointer to the data part (i.e both parameters and values 
 *          or values only based on the coomand)
 * @param cmd         a pointer to the command string
 * @param cmd_len     the length of the command string  
 * @param data        a pointer to the data string (both parameters and values pairs)
 * @param data_len    the length of the data string
 * @return void 
 */
void uart_handle_cmd(USART_TypeDef * usartx,uint8_t * cmd,size_t cmd_len, uint8_t * data, size_t data_len)
{
  
  if(strcasecmp((const char *)cmd,"run")==0)
  {
	  uart_run_cmd_handle(usartx);
  } 
  else if(strcasecmp((const char *)cmd,"hlt")==0)
  {
	  uart_hlt_cmd_handle(usartx);
  }
  else if(strcasecmp((const char *)cmd,"init")==0)
  {
	  uart_init_cmd_handle(usartx);
  }
  else if(strcasecmp((const char *)cmd,"info")==0)
  {
	  uart_info_cmd_handle(usartx);
  }
  else if(strcasecmp((const char *)cmd,"read")==0)
  {

	  uart_read_cmd_handle(usartx,data,data_len);
  }    
  else if(strcasecmp((const char *)cmd,"write")==0)
  {
	  uart_write_cmd_handle(usartx,data,data_len);
  }    
  else if(strcasecmp((const char *)cmd,"who")==0)
  {
	  uart_who_cmd_handle(usartx);
  }    
  else if(strcasecmp((const char *)cmd,"smpl")==0)
  {
	  uart_smpl_cmd_handle(usartx,data,data_len);
  }    
  else if(strcasecmp((const char *)cmd,"rng")==0)
  {
	  uart_rng_cmd_handle(usartx,data,data_len);
  }    
  else if(strcasecmp((const char *)cmd,"lpf")==0)
  {
	  uart_lpf_cmd_handle(usartx,data,data_len);
  }    
  else if(strcasecmp((const char *)cmd,"hpf")==0)
  {
	  uart_hpf_cmd_handle(usartx,data,data_len);
  }    
  else if(strcasecmp((const char *)cmd,"clk")==0)
  {
	 uart_clk_cmd_handle(usartx,data,data_len);
  } 
  else if(strcasecmp((const char *)cmd,"rst")==0)
  {
	 uart_rst_cmd_handle(usartx);
  } 
  else if(strcasecmp((const char *)cmd,"tst")==0)
  {
	  uart_tst_cmd_handle(usartx,data,data_len);
  } 
  else if(strcasecmp((const char *)cmd,"cyc")==0)
  {
	  uart_cyc_cmd_handle(usartx,data,data_len);
  } 
  else
  {
    uart_println(usartx,"incorrect command/parameter ....!");
  }
}
//------------------------------------------------------------------------------------------------------------
//********************************************************************************************
//
//  uart commands Prototype function
//
//********************************************************************************************
/**
 * @brief force system to run/stop  data acquestion of MPU6050 sensors
 * @details 
 * @return  
 */
void  uart_run_cmd_handle(USART_TypeDef * usartx)
{
//! run command: force system to run/stop  data acquestion of MPU6050 sensors
 uart_println(usartx,"run acquestion for MPU6050 cmd .....");  
  mpu_settings.acq_run=1;//mpu_acq_run=1;
}
//-----------------------------------------------------------------------------
/**
 * @brief handle the halt command
 * 
 * @details this method handle the blink command which request 
 *          to deactivate of the bliniking task 
 * @return void
 */
void  uart_hlt_cmd_handle(USART_TypeDef * usartx)
{
  uart_println(usartx,"halt acquestion for MPU6050 cmd .....");  
  mpu_settings.acq_run=0;//mpu_acq_run=0;
}
//------------------------------------------------------------------------------------------------------------
/**
 * @brief init command: initialize MPU6050 Module
 * @details 
 * @return  
 */
void  uart_init_cmd_handle(USART_TypeDef * usartx)
{
 uint8_t error=0;
//! init command: initialize MPU6050 Module
  uart_println(usartx,"initialization MPU6050 cmd .....");  
  i2c_init_std(MPU6050_I2C,MPU6050_I2C_CLOCK,0x20);
  error=mpu6050_init((MPU6050_t *)&myMPU6050,MPU6050_Accel_Range_2G,MPU6050_Gyro_Range_500s);
  if(error != I2C_OK)
  {
	uart_print(usartx,"Failed to initialize the MPU6050 ER::");
	uart_print_integer(usartx,error,10);
	return ;
  }
  uart_println(usartx,"initialization MPU6050 Done .....");  

}
//-----------------------------------------------------------------------------
/**
 * @brief info command: returns specific info about the mpu6050
 * @details 
 * @return  
 */
void  uart_rst_cmd_handle(USART_TypeDef * usartx)
{
 uint8_t error=0;
//! reset command: reset MPU6050 Module
  uart_println(usartx,"Reset MPU6050 cmd .....");  
  error=mpu6050_reset((MPU6050_t*)&myMPU6050);
  if(error==I2C_OK)
  uart_print(usartx,"MPU6050 successfully Reset ");
  else
  {
	uart_print(usartx,"Error:0x");
	uart_print_integer(usartx,error,16);
    uart_print(usartx,"\t failed to reset MPU6050 ");
  }
   
}
//-----------------------------------------------------------------------------
/**
 * @brief info command: returns specific info about the mpu6050
 * @details 
 * @return  
 */
void  uart_info_cmd_handle(USART_TypeDef * usartx)
{
//! init command: initialize MPU6050 Module

}
//-----------------------------------------------------------------------------
/**
 * @brief who command: returns WHO_IAM register content 
 * @details the WHOIAM is (reg@0x75)::0x68 
 * @return  
 */
void  uart_who_cmd_handle(USART_TypeDef * usartx)
{
//! init command: initialize MPU6050 Module
uint8_t temp=0, error=0;
uart_print(usartx,"MPU6050_WHO_AM_I  :");	
error=i2c_read_7bit_base_byte_std(MPU6050_I2C, myMPU6050.Address, MPU6050_WHO_AM_I , &temp);
if(error==I2C_OK)
  uart_print_integer(usartx,temp,16);
else
 {
  uart_print(usartx,"Error:0x");
  uart_print_integer(usartx,error,16);
  uart_print(usartx,"\t failed to read MPU6050 ");
 }
   
 uart_print(usartx,"\r\n");
}
//-----------------------------------------------------------------------------
/**
 * @brief 	read command that could be a specific register or sensor of MPU6050
 * @details read command allow to specify different types of read operation 
 * 			such as read register, 
 * 					read accelometer, 
 * 					read gyroscope, 
 * 					read temperature
 * 					read all 
 * @return  void
 */
void  uart_read_cmd_handle(USART_TypeDef * usartx,uint8_t * data, size_t data_len)
{
  int len=0;
  uint8_t list_len=0,i=0;
  uint8_t error=0;
  cmd_t command;
  param_t p={0};
  command.cmd=0;
  char buf[16]="";
  uart_println(usartx,"read command ....");
  list_len= cmd_split(data,data_len,'-',(cmd_t*)&command);
  uart_print(usartx,"read command parameter len:");
  uart_print_integer(usartx,list_len,10);
  uart_print(usartx,"\r\n");
  
  if(list_len>0)
  {
    for(i=0;i<command.param_len;i++)
	{
	  len=param_split(command.parameters[i],(param_t*)&p);
    if(p.param_len> 0)
    {
		 memset(buf,0,16);
   	 memcpy(buf,p.param,p.param_len);
		 uart_print(usartx,"parm:");
		 uart_println(usartx,buf);
    }
    if(p.data_len>0)
    {
		 memset(buf,0,16);
   	 memcpy(buf,p.data,p.data_len);
		 uart_print(usartx,"data:");
		 uart_println(usartx,buf);
    }
	  if(len>0)
	  {
		 error= uart_read_cmd_param_exe(usartx,p);
		 if(error!=I2C_OK)
		 {
			uart_println(usartx,"Failed to execute the read Command ...");
			uart_print(usartx,"ERR::0x");
			uart_print_integer(usartx,error,16);
		 }
	  }
	}
  }
}
//-----------------------------------------------------------------------------
/**
 * @brief 	write command that could be a specific register of MPU6050
 * @details write command allow to write to specific register 
 * @return  void
 */
void  uart_write_cmd_handle(USART_TypeDef * usartx,uint8_t * data, size_t data_len)
{
//! write register command: write to aspecific register in MPU6050 Module
  int len=0;
  uint8_t list_len=0,i=0;
  uint8_t error=0;
  uint8_t reg_address=0, reg_val=0;
  cmd_t command;
  param_t p={0};
  command.cmd=0;
  char buf[16]="";

  list_len= cmd_split(data,data_len,'-',(cmd_t*)&command);
  if(list_len>0)
  {
   for(i=0;i<command.param_len;i++)
	 {
	   len=param_split(command.parameters[i],(param_t*)&p);
       if(p.param_len> 0)
       {
		    memset(buf,0,16);
   	    memcpy(buf,p.param,p.param_len);
		    uart_print(usartx,"parm:");
		    uart_println(usartx,buf);
       }
       if(p.data_len>0)
       {
		    memset(buf,0,16);
   		  memcpy(buf,p.data,p.data_len);
		    uart_print(usartx,"data:");
		    uart_println(usartx,buf);
       }
	   if(len>0)
     {

		    uart_write_cmd_param_exe(usartx,p,(uint8_t*)&reg_address,(uint8_t*)&reg_val);
	   }
	 }
	 if(reg_address>=0x0d && reg_address<=0x75)
	 {
	   error=uart_write_reg_exe(usartx,(MPU6050_t*)&myMPU6050,reg_address,reg_val);
	   if(error!=I2C_OK)
	   {
			uart_println(usartx,"Failed to execute the write Command ...");
			uart_print(usartx,"ERR::0x");
			uart_print_integer(usartx,error,16);
	   }
  	}
  }
}
//-----------------------------------------------------------------------------
/**
 * @brief
 * @details 
 * @return  
 */
uint8_t uart_smpl_cmd_handle(USART_TypeDef * usartx,uint8_t * data, size_t data_len)
{
 uint8_t sample_rate=0;  
  char  buf[16]="";
  sample_rate=atol((const char *)data);  

 uint8_t error=0;
 error=mpu6050_setDataRate((MPU6050_t*)&myMPU6050,sample_rate);
 if(error==I2C_OK) 
  {
	uart_print(usartx,"Sample data rate is set to 0x");
	uart_print_integer(usartx,sample_rate,16);	
  }
  return error;
}
//-----------------------------------------------------------------------------
/**
 * @brief
 * @details 
 * @return  
 */
void  uart_rng_cmd_handle(USART_TypeDef * usartx,uint8_t * data, size_t data_len)
{

}
//-----------------------------------------------------------------------------
/**
 * @brief
 * @details 
 * @return  
 */
uint8_t  uart_lpf_cmd_handle(USART_TypeDef * usartx,uint8_t * data, size_t data_len)
{
//! Read temp command: read only accelometer sensor in MPU6050 Module 
 uint8_t lpf=0;  
  char  buf[16]="";
  lpf=atol((const char *)data);  

 uint8_t error=0;
 error=mpu6050_set_lpf((MPU6050_t*)&myMPU6050,lpf);
 if(error==I2C_OK) 
  {
	uart_print(usartx,"lpf rate is set to 0x");
	uart_print_integer(usartx,lpf,16);	
  }
  return error;
}
//-----------------------------------------------------------------------------
/**
 * @brief
 * @details 
 * @return  
 */
uint8_t  uart_hpf_cmd_handle(USART_TypeDef * usartx,uint8_t * data, size_t data_len)
{
uint8_t hpf=0;  
  char  buf[16]="";
  hpf=atol((const char *)data);  

 uint8_t error=0;
 error=mpu6050_set_lpf((MPU6050_t*)&myMPU6050,hpf);
 if(error==I2C_OK) 
  {
	uart_print(usartx,"hpf rate is set to 0x");
	uart_print_integer(usartx,hpf,16);	
  }
  return error;
}
//-----------------------------------------------------------------------------
/**
 * @brief
 * @details 
 * @return  
 */
void  uart_clk_cmd_handle(USART_TypeDef * usartx,uint8_t * data, size_t data_len)
{

}
//-----------------------------------------------------------------------------
/**
 * @brief
 * @details 
 * @return  
 */
void  uart_tst_cmd_handle(USART_TypeDef * usartx,uint8_t * data, size_t data_len)
{

}
//-----------------------------------------------------------------------------
/**
 * @brief
 * @details 
 * @return  
 */
void  uart_cyc_cmd_handle(USART_TypeDef * usartx,uint8_t * data, size_t data_len)
{
  uint32_t val=0;  
  char  buf[16]="";
  val=atol((const char *)data);  

  if(val >=10 && val<1000)
  {
   mpu_cycle =10000U* val;  
   uart_println(usartx,"cycle is changed .....");
  }
  else
  {
   mpu_cycle=MPU_WAIT_TIMEOUT;
   uart_println(usartx,"cycle speed is fast than the allowed upper limit  .....\r\n");  
  }

   uart_print(usartx,"current cycle speed:");
   utoa(mpu_cycle,buf,10);
   uart_println(usartx,buf);
}
//-----------------------------------------------------------------------------




//********************************************************************************************
//
// uart sub commaond command and frame handling definition
//
//********************************************************************************************
void uart_write_cmd_param_exe(USART_TypeDef * usartx,param_t p, uint8_t * reg_address, uint8_t * reg_val)
{
 char buf[16]="";
 int val=-1; 
 if(p.data_len>0)
  {
    memset(buf,0,16);
    memcpy(buf,p.data,p.data_len);
    val=atol((const char *)buf); 
  }
   memset(buf,0,16);
   memcpy(buf,p.param,p.param_len);
  
  if(strcasecmp((const char *)buf,"-r")==0)
  {
	if(val >= 0x0D && val <=0x75)
	  *reg_address=val;
  }
  else if(strcasecmp((const char *)buf,"-v")==0)
  {
	*reg_val=val;
  }          
 else
 {
	uart_print(usartx,"unknown parameter :");
  	uart_println(usartx,(char *)buf);
 }
}
//-----------------------------------------------------------------------------
uint8_t uart_write_reg_exe(USART_TypeDef * usartx, MPU6050_t * mpu,uint8_t reg_address, uint8_t reg_val)
{
 uint8_t error=0, temp=0;
 error=i2c_write_7bit_base_byte_std(MPU6050_I2C, mpu->Address, reg_address, reg_val);
 if(error==I2C_OK) 
  {
	uart_print(usartx,"reg(@0x");
	uart_print_integer(usartx,reg_address,16);
	uart_print(usartx,") has written the value 0x");
	uart_print_integer(usartx,reg_val,16);	
  }
  return error;
  }
//-----------------------------------------------------------------------------

uint8_t uart_read_cmd_param_exe(USART_TypeDef * usartx,param_t p)
{
 char buf[16]="";
 int val=-1; 
 uint8_t error=0;
 if(p.data_len>0)
  {
    memset(buf,0,16);
    memcpy(buf,p.data,p.data_len);
    val=atol((const char *)buf); 
  }
//   memset(buf,0,16);
//   memcpy(buf,p.param,p.param_len);
    //if(p.param_len> 0)
    {
		    memset(buf,0,16);
   	    memcpy(buf,p.param,p.param_len);
		    uart_print(usartx,"buf:");
		    uart_println(usartx,buf);
    }
  if(strcasecmp((const char *)buf,"-r")==0)
  {
	  if(val >= 0x0D && val <=0x75)
	    error=uart_read_reg_exe(usartx,(MPU6050_t*)&myMPU6050,val);
  }
  else if(strcasecmp((const char *)buf,"-all")==0)
  {
	    error=uart_read_all_exe(usartx,(MPU6050_t*)&myMPU6050);	
  }          
  else if(strcasecmp((const char *)buf,"-a")==0)
  {
	    error=uart_read_accelerometer_exe(usartx,(MPU6050_t*)&myMPU6050);
  }          
 else if(strcasecmp((const char *)buf,"-g")==0)
 {
	    error=uart_read_gyroscope_exe(usartx,(MPU6050_t*)&myMPU6050);
 }          
 else if(strcasecmp((const char *)buf,"-t")==0)
 {
	    error=uart_read_temperature_exe(usartx,(MPU6050_t*)&myMPU6050);
 }          
 else
 {
	  uart_print(usartx,"unknown parameter :");
  	uart_println(usartx,(char *)buf);
 }
  return error;
}
//-----------------------------------------------------------------------------
uint8_t uart_read_reg_exe(USART_TypeDef * usartx, MPU6050_t * mpu,uint8_t reg_address)
{
 uint8_t error=0, temp=0;
 error=i2c_read_7bit_base_byte_std(MPU6050_I2C, mpu->Address, reg_address, &temp);
 if(error==I2C_OK) 
  {
	uart_print(usartx,"reg(@0x");
	uart_print_integer(usartx,reg_address,16);
	uart_print(usartx,"): 0x");
	uart_print_integer(usartx,temp,16);
	
  }
  return error;
  }
//-----------------------------------------------------------------------------
uint8_t uart_read_all_exe(USART_TypeDef * usartx,MPU6050_t * mpu)
{
	uint8_t error=0;
	error=mpu6050_read_All((MPU6050_t *)mpu);
	if(error==I2C_OK)
	{
		uart_println (usartx,"...............");
		uart_println (usartx,"MPU6050 integer Data ...");
		mpu6050_uart_print_All(usartx,mpu);			  
		uart_println (usartx,"MPU6050 Hex Data ...");
		mpu6050_uart_print_raw_Data(usartx,mpu);
		uart_println (usartx,"MPU6050 Raw Data ...");
		mpu6050_uart_print_raw_Array(usartx,mpu);
		uart_println (usartx,"...............");						
	}
	return error;
}
//-----------------------------------------------------------------------------
uint8_t uart_read_accelerometer_exe(USART_TypeDef * usartx,MPU6050_t * mpu)
{
	uint8_t error=0;
	error=mpu6050_read_Accelerometer(mpu);
	if(error==I2C_OK)
	{
		uart_println (usartx,"...............");
		uart_println (usartx,"MPU6050 Accelerometer Data ...");
		mpu6050_uart_print_Accelometer(usartx,mpu);			  
		uart_println (usartx,"MPU6050 Accelerometer Hex Data ...");
		mpu6050_uart_print_raw_Accelometer(usartx,mpu);
		uart_println (usartx,"...............");						
	}
	return error;
}
//-----------------------------------------------------------------------------
uint8_t uart_read_gyroscope_exe(USART_TypeDef * usartx,MPU6050_t * mpu)
{
	uint8_t error=0;
	error=mpu6050_read_Gyroscope(mpu);
	if(error==I2C_OK)
	{
		uart_println (usartx,"...............");
		uart_println (usartx,"MPU6050 Gyroscope Data ...");
		mpu6050_uart_print_Gyroscope(usartx,mpu);			  
		uart_println (usartx,"MPU6050 Gyroscope Hex Data ...");
		mpu6050_uart_print_raw_Gyroscope(usartx,mpu);
		uart_println (usartx,"...............");						
	}
	return error;
}
//-----------------------------------------------------------------------------
uint8_t uart_read_temperature_exe(USART_TypeDef * usartx,MPU6050_t * mpu)
{
	uint8_t error=0;
	error=mpu6050_read_Temperature(mpu);
	if(error==I2C_OK)
	{
		uart_println (usartx,"...............");
		uart_println (usartx,"MPU6050 Temperature Data ...");
		mpu6050_uart_print_Temperature(usartx,mpu);			  
		uart_println (usartx,"MPU6050 Temperature Hex Data ...");
		mpu6050_uart_print_raw_Temperature(usartx,mpu);
		uart_println (usartx,"...............");						
	}
	return error;
}
//-----------------------------------------------------------------------------
