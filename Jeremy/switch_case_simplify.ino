void switchCaseSimplify(int val){
  
  switch(val)
  {
    case 0:
    break;

    case 1:
    if(servopos1<160)
    servopos1+=5;
    break;
    
     case 2:
    if(servopos1>10)
    servopos1-=5;
    break;

     case 3:
    if(servopos2<80)
    servopos2+=5;
    break;

     case 4:
    if(servopos2>5)
    servopos2-=5;
    break;

   case 5:
   break;
  }
}
