.name       "Batman"
.comment    "This city needs me"

marker:				
					
				
loop:            
		sti       r1       ,        %:live      ,			%1			

live: live		%255			
			ld		 %2555,r2		
        zjmp	 %:loop			
