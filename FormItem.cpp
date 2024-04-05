#include "stdafx.h"
#include "FormItem.h"

    short& FormItem::getFIType(){
        return fi_type;
    }

    short& FormItem::getFIState(){
        return fi_state;
    }

    short* FormItem::getFIPState(){
        return &fi_state;
    }
    
    void FormItem::setFIState(short state){
        fi_state = state;
    }

    void FormItem::formEInput(Event event){
    }
