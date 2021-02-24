.name       "Batman"
.comment    "This city needs me"

marker:				
					
				
loop:            
		sti       r1       ,        %255      ,			%255			

live: live		%0			
			ld		 %0,r2		
        zjmp	 %:loop			
