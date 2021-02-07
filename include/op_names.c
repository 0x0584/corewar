const char	*g_op_names[op_count] = {	
	[op_live]   = "live",  									 
                        
	[op_zjmp]   = "zjmp",   
                       
	[op_add]    = "add",    
	[op_sub]    = "sub",    
	[op_and]    = "and",    
	[op_or]     = "or",     
	[op_xor]    = "xor",    
                       
	[op_ld]     = "ld",    
	[op_st]     = "st",     
	[op_ldi]    = "ldi",    
	[op_sti]    = "sti",    
	[op_lld]    = "lld",    
	[op_lldi]   = "lldi",   
                       
	[op_fork]   = "fork",   
	[op_lfork]  = "lfork",  
                       
	[op_aff]    = "aff",    
                        
	[op_nop]	= "nop"
};
