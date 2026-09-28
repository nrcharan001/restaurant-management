//om//
#include<stdio.h>
#include<string.h>
#define MAX_ITEMS 10
#define MAX_ORDERS 10
#define RESTAURANTS 15
struct area{
    char name[20];
    int pincode;
};
struct order_item{
    char name[20];
    int quantity;

};
struct item{
    char name[20];
    float price;
    int service_time;
};
struct order{
    char customer_name[50];
    struct area area;
    long long int ph_no;
    int quantity;
    struct order_item o_it[MAX_ORDERS];
};
struct restaurant{
    char name[20];
    struct area area;
    struct item item[MAX_ITEMS];
    int item_count;
    struct item spl_item[MAX_ITEMS];
    int spl_item_count;
    struct item item_of_day;
    struct order orders_record[MAX_ORDERS];
    int order_count;
};
struct rest_name{
    char name[20];
};
struct spl_full {
    char item_name[20];
    float price;
    char rest_name[20];
    char area_name[20];
};


int distance[5][5]={
    {0, 2, 4, 6, 8},
    {2, 0, 3, 5, 7},
    {4, 3, 0, 2, 4},
    {6, 5, 2, 0, 3},
    {8, 7, 4, 3, 0}
};
int get_distance(struct area a1, struct area a2, int distance[5][5]){
    int index1 = a1.pincode % 5;
    int index2 = a2.pincode % 5;
    return distance[index1][index2];
}

void sort_restaurants(struct restaurant r[], int n){
    int sorted = 0;
    for(int i=0;i<n-1 && !sorted;i++){
        sorted = 1;
        for(int j=0;j<n-i-1 ;j++){
            if(strcmp(r[j].name,r[j+1].name)>0){
                struct restaurant temp = r[j];
                r[j] = r[j+1];
                r[j+1] = temp;
                sorted = 0;
            }
            else if(strcmp(r[j].name,r[j+1].name)==0){
                if(strcmp(r[j].area.name,r[j+1].area.name)>0){
                    struct restaurant temp = r[j];
                    r[j] = r[j+1];
                    r[j+1] = temp;
                    sorted = 0;
                }
            }
        }
    }
} 
// sorts items in their respcetive types
void sort_items_by_name(struct restaurant r[], int n){
    for(int i=0;i<n;i++){
        //bubble sort
        //sorting normal items
        int sorted = 0;
        for(int j=0;j<r[i].item_count-1 && !sorted;j++){
            sorted = 1;
            for(int k=0;k<r[i].item_count-j-1;k++){
                if(strcmp(r[i].item[k].name,r[i].item[k+1].name)>0){
                    struct item temp = r[i].item[k];
                    r[i].item[k] = r[i].item[k+1];
                    r[i].item[k+1] = temp;
                    sorted = 0;
                }
            }
        }
        //sorting spl items
        sorted = 0;
        for(int j=0;j<r[i].spl_item_count-1 && !sorted;j++){
            sorted = 1;
            for(int k=0;k<r[i].spl_item_count-j-1;k++){
                if(strcmp(r[i].spl_item[k].name,r[i].spl_item[k+1].name)>0){
                    struct item temp = r[i].spl_item[k];
                    r[i].spl_item[k] = r[i].spl_item[k+1];
                    r[i].spl_item[k+1] = temp;
                }
            }
        }
    }
}
// this takes stuct item as input 
void sort_item_by_name(struct item items[], int count){
    int sorted = 0;
    for(int i=0;i<count-1 && !sorted;i++){
        sorted = 1; 
        for(int j=0;j<count-i-1;j++){
            if(strcmp(items[j].name,items[j+1].name)>0){
                struct item temp = items[j];
                items[j] = items[j+1];
                items[j+1] = temp;
                sorted = 0;
            }
        }
    }

}


void sort_special_items(struct restaurant r[], int n){
    for(int i=0;i<n;i++){
            int sorted = 0;
        for(int j=0;j<r[i].spl_item_count-1 && !sorted;j++){
            sorted = 1;
            for(int k=0;k<r[i].spl_item_count-j-1;k++){
                if(strcmp(r[i].spl_item[k].name,r[i].spl_item[k+1].name)>0){
                    struct item temp = r[i].spl_item[k];
                    r[i].spl_item[k] = r[i].spl_item[k+1];
                    r[i].spl_item[k+1] = temp;
                    sorted = 0;
                }
            }
        }
        for(int j=0;j<r[i].spl_item_count;j++){
            printf("%s, price: %.2f\n", r[i].spl_item[j].name, r[i].spl_item[j].price);
        }
    }
}
int GetMinTime(struct restaurant r[],char item_name[], struct area customer_area,int quantity,int n,int order){
    int min_time = 1000000;
    int pos;
    char best_restaurant[20];
    for(int i=0;i<n;i++){
        int item_found = 0;
        for(int j=0;j<r[i].item_count && !item_found;j++){
            if(strcmp(r[i].item[j].name,item_name)==0){
                int delivery_time = (r[i].item[j].service_time*quantity) + get_distance(r[i].area, customer_area, distance);
                if(delivery_time<min_time){
                    min_time = delivery_time;
                    strcpy(best_restaurant, r[i].name);
                    pos=i;
                }
                item_found = 1;
            }
        }
    }
    if(order==0){
         if(min_time==1000000){
        printf("Item not found in any restaurant.\n");
        }
        else{
        printf("Best restaurant for %s is %s with delivery time %d minutes.\n restaurant address: %s \n", item_name, best_restaurant, min_time, r[pos].area.name);
        }
    }
    return pos;
    
}

void getItemAvailability(struct restaurant r[], char item_name[], int n){
    printf("Restaurants offering %s:\n", item_name);
    for(int i=0;i<n;i++){
        int found = 0;
        for(int j=0;j<r[i].item_count && !found;j++){
            if(strcmp(r[i].item[j].name,item_name)==0){
                printf("%s,price: %.2f\n", r[i].name, r[i].item[j].price);
                found=1;
            }
        }
    }
}
void getItemListSortedByPrice(struct restaurant r[],int n,char restaurant_name[]){
    int found = 0;
    int pos;

    struct item all_items[50];
    int count = 0;

    for(int i=0;i<n && !found;i++){
        if(strcmp(r[i].name,restaurant_name)==0){
            pos=i;
            found=1;

            // normal items
            for(int j=0;j<r[i].item_count;j++){
                all_items[count++] = r[i].item[j];
            }

            // special items
            for(int j=0;j<r[i].spl_item_count;j++){
                all_items[count++] = r[i].spl_item[j];
            }

            // item of day
            all_items[count++] = r[i].item_of_day;
        }
    }

    if(!found){
        printf("Restaurant not found\n");
        return;
    }
    int sorted = 0;
    for(int i=0;i<count-1 && !sorted;i++){
        sorted = 1;
        for(int j=0;j<count-i-1;j++){
            if(all_items[j].price > all_items[j+1].price){
                struct item temp = all_items[j];
                all_items[j] = all_items[j+1];
                all_items[j+1] = temp;
                sorted = 0;
            }
        }
    }

    printf("All items in %s sorted by price:\n", restaurant_name);
    for(int i=0;i<count;i++){
        printf("%s, price: %.2f\n", all_items[i].name, all_items[i].price);
    }
}
void getItemListInSortedOrder(struct restaurant r[],int n,char restaurant_name[]){
    int found = 0;
    int pos;

    struct item all_items[50];
    int count = 0;

    for(int i=0;i<n && !found;i++){
        if(strcmp(r[i].name,restaurant_name)==0){
            pos=i;
            found=1;

            // normal items
            for(int j=0;j<r[i].item_count;j++){
                all_items[count++] = r[i].item[j];
            }

            // special items
            for(int j=0;j<r[i].spl_item_count;j++){
                all_items[count++] = r[i].spl_item[j];
            }

            // item of day
            all_items[count++] = r[i].item_of_day;
        }
    }

    if(!found){
        printf("Restaurant not found\n");
        return;
    }

    sort_item_by_name(all_items, count);

    printf("All items in %s sorted by name:\n", restaurant_name);
    for(int i=0;i<count;i++){
        printf("%s, price: %.2f\n", all_items[i].name, all_items[i].price);
    }
}
void splitemsinsorted(struct rest_name rn[], int k, struct restaurant r[], int n){
    struct spl_full spl_it[100];
    int count = 0;

    for(int i=0;i<k;i++){
        for(int j=0;j<n;j++){
            if(strcmp(rn[i].name, r[j].name)==0){
                for(int l=0;l<r[j].spl_item_count;l++){

                    strcpy(spl_it[count].item_name, r[j].spl_item[l].name);
                    spl_it[count].price = r[j].spl_item[l].price;
                    strcpy(spl_it[count].rest_name, r[j].name);
                    strcpy(spl_it[count].area_name, r[j].area.name);

                    count++;
                }
            }
        }
    }
    int sorted = 0;
    for(int i=0;i<count-1 && !sorted;i++){
        sorted = 1;
        for(int j=0;j<count-i-1;j++){
            if(strcmp(spl_it[j].item_name, spl_it[j+1].item_name) > 0 ||
              (strcmp(spl_it[j].item_name, spl_it[j+1].item_name)==0 &&
               spl_it[j].price > spl_it[j+1].price)){

                struct spl_full temp = spl_it[j];
                spl_it[j] = spl_it[j+1];
                spl_it[j+1] = temp;
                sorted = 0;
            }
        }
    }


    printf("Special items in sorted order:\n");
    for(int i=0;i<count;i++){
        printf("%s, price: %.2f, restaurant: %s, area: %s\n",
            spl_it[i].item_name,
            spl_it[i].price,
            spl_it[i].rest_name,
            spl_it[i].area_name);
    }
}
  
void GetItemListInAreaSortedOrder(struct restaurant r[], int n, struct order o){
    struct restaurant area_restaurants[RESTAURANTS];
    int count = 0;
    for(int i=0;i<n;i++){
        if(r[i].area.pincode==o.area.pincode){
            area_restaurants[count] = r[i];
            count++;
        }
    }
    sort_restaurants(area_restaurants, count);
    printf("Restaurants near your area:\n");
    for(int i=0;i<count;i++){
        printf("%s\n", area_restaurants[i].name);
        for(int j=0;j<area_restaurants[i].item_count;j++){
            printf("  %s, price: %.2f\n", area_restaurants[i].item[j].name, area_restaurants[i].item[j].price);
        }
    }

}
void GetItemOfDayInSortedorder(struct restaurant r[],int n){
    struct item item_of_day[RESTAURANTS];
    int count = 0;
    for(int i=0;i<n;i++){
            item_of_day[count] = r[i].item_of_day;
            count++;
        
    }
    sort_item_by_name(item_of_day, count);
    printf("Item of the day\n");
    for(int i=0;i<count;i++){
        printf("%s, price: %.2f\n", item_of_day[i].name, item_of_day[i].price);
    }
}
int GetCommonItemsInSorted(struct restaurant r[],int n,struct item common_items[], int count){
    struct item base[50];
    int base_count = 0;
    for(int i=0;i<r[0].item_count;i++){
        base[base_count++] = r[0].item[i];
    }
    for(int i=0;i<r[0].spl_item_count;i++){
        base[base_count++] = r[0].spl_item[i];
    }
    base[base_count++] = r[0].item_of_day;
    for(int i=0;i<base_count;i++){
        int isCommon = 1;
        for(int j=1;j<n;j++){
            int found = 0;
            for(int k=0;k<r[j].item_count;k++){
                if(strcmp(base[i].name, r[j].item[k].name)==0){
                    found = 1;
                    break;
                }
            }
            for(int k=0;k<r[j].spl_item_count && !found;k++){
                if(strcmp(base[i].name, r[j].spl_item[k].name)==0){
                    found = 1;
                    break;
                }
            }
            if(!found){
                if(strcmp(base[i].name, r[j].item_of_day.name)==0){
                    found = 1;
                }
            }
            if(!found){
                isCommon = 0;
                break;
            }
        }
        if(isCommon){
            common_items[count++] = base[i];
        }
    }
    sort_item_by_name(common_items, count);
    if(count==0){
        printf("No common items found.\n");
    } else {
        for(int i=0;i<count;i++){
            printf("%s, price: %.2f\n", common_items[i].name, common_items[i].price);
        }
    }
    return count;
}
int GetUniqueItemsInSorted(struct restaurant r[], int n, struct item unique_items[], int count) {
    struct item temp[300];
    int freq[300];
    int tempCount = 0;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < r[i].item_count; j++){
            int found = -1;
            for(int k = 0; k < tempCount; k++){
                if(strcmp(temp[k].name, r[i].item[j].name) == 0){
                    found = k;
                    break;
                }
            }
            if(found == -1){
                temp[tempCount] = r[i].item[j];
                freq[tempCount++] = 1;
            } else {
                freq[found]++;
            }
        }

        for(int j = 0; j < r[i].spl_item_count; j++){
            int found = -1;
            for(int k = 0; k < tempCount; k++){
                if(strcmp(temp[k].name, r[i].spl_item[j].name) == 0){
                    found = k;
                    break;
                }
            }
            if(found == -1){
                temp[tempCount] = r[i].spl_item[j];
                freq[tempCount++] = 1;
            } else {
                freq[found]++;
            }
        }

        int found = -1;
        for(int k = 0; k < tempCount; k++){
            if(strcmp(temp[k].name, r[i].item_of_day.name) == 0){
                found = k;
                break;
            }
        }
        if(found == -1){
            temp[tempCount] = r[i].item_of_day;
            freq[tempCount++] = 1;
        } else {
            freq[found]++;
        }
    }

    for(int i = 0; i < tempCount; i++){
        if(freq[i] == 1){
            unique_items[count++] = temp[i];
        }
    }

    sort_item_by_name(unique_items, count);

    if(count == 0){
        printf("No unique items found.\n");
    } else {
        for(int i = 0; i < count; i++){
            printf("%s, price: %.2f\n", unique_items[i].name, unique_items[i].price);
        }
    }

    return count;
}
int addRestaurant(struct restaurant r[],int n)
{
    int index=n-1;
    int new_count;
    printf("Enter no of restaurants to be added: ");
    scanf("%d", &new_count);
    for(int i=0;i<new_count;i++){
        printf("Enter restaurant name: ");
        scanf(" %[^\n]", r[index].name);
        printf("Enter area name: ");
        scanf(" %[^\n]", r[index].area.name);
        printf("Enter area pincode: ");
        printf("(4400-4404) : ");
        scanf("%d", &r[index].area.pincode);
        printf("Enter number of items: ");
        scanf("%d", &r[index].item_count);
        for(int j=0;j<r[index].item_count;j++){
            printf("Enter item name: ");
            scanf(" %[^\n]", r[index].item[j].name);
            printf("Enter item price: ");
            scanf("%f", &r[index].item[j].price);
            printf("Enter item service time: ");
            scanf("%d", &r[index].item[j].service_time);
        }
        printf("Enter number of special items: ");
        scanf("%d", &r[index].spl_item_count);
        for(int j=0;j<r[index].spl_item_count;j++){
            printf("Enter special item name: ");
            scanf(" %[^\n]", r[index].spl_item[j].name);
            printf("Enter special item price: ");
            scanf("%f", &r[index].spl_item[j].price);
            printf("Enter special item service time: ");
            scanf("%d", &r[index].spl_item[j].service_time);
        }
            printf("Enter item of day name: ");
            scanf(" %[^\n]", r[index].item_of_day.name);
            printf("Enter item of day price: ");
            scanf("%f", &r[index].item_of_day.price);
            printf("Enter item of day service time: ");
            scanf("%d", &r[index].item_of_day.service_time);
            
        index++;
    }
    return new_count;
}
int confirmOrder(struct restaurant r[], char restaurant_name[],struct order o,
                 char item_name[], int quantity,
                 struct area customer_area,
                 int n, int* time) {

    for(int i = 0; i < n; i++) {
        if(strcmp(r[i].name, restaurant_name) == 0) {

            for(int j = 0; j < r[i].item_count; j++) {
                if(strcmp(r[i].item[j].name, item_name) == 0) {
                    //copy user deatils and order detilas to restaurant's order record
                    //only those items which are ordered in this order should be copied to restaurant's order record
                  int idx = r[i].order_count;

					strcpy(r[i].orders_record[idx].customer_name, o.customer_name);
					r[i].orders_record[idx].area = o.area;
					r[i].orders_record[idx].ph_no = o.ph_no;
					r[i].orders_record[idx].quantity = quantity;
					r[i].orders_record[idx].o_it[0].quantity = quantity;
					strcpy(r[i].orders_record[idx].o_it[0].name, item_name);
					r[i].order_count++;                 
                    *time = (r[i].item[j].service_time * quantity)
                            + get_distance(r[i].area, customer_area, distance);
                    return quantity * r[i].item[j].price;
                }
            }
        }
    }
    printf("ERROR: Item not found in selected restaurant\n");
    return 0;
}
int placeOrder(struct restaurant r[], struct order o, int n, int order_count){
    int max = 0;
    int sum = 0;

    for(int i = 0; i < order_count; i++){
        printf("Where do you want to order %s from?\n", o.o_it[i].name);
        printf("1: select fastest restaurant\n");
        printf("2: choose manually\n");

        int choice;
        scanf("%d", &choice);

        int time;

        switch(choice){
            case 1:{
                int pos = GetMinTime(r, o.o_it[i].name, o.area, o.o_it[i].quantity, n, 1);

                sum += confirmOrder(r, r[pos].name, o,
                                    o.o_it[i].name, o.o_it[i].quantity,
                                    o.area, n, &time);

                if(time > max) max = time;
                break;
            }

            case 2:{
                getItemAvailability(r, o.o_it[i].name, n);

                char restaurant_name[20];
                printf("Enter restaurant name: ");
                scanf(" %[^\n]", restaurant_name);

                sum += confirmOrder(r, restaurant_name, o,
                                    o.o_it[i].name, o.o_it[i].quantity,
                                    o.area, n, &time);

                if(time > max) max = time;
                break;
            }

            default:
                printf("Invalid choice\n");
        }
    }
printf("Order placed successfully!\n");
    printf("Order details:\n");
    printf("Customer Name: %s\n", o.customer_name);
    printf("Area: %s\n", o.area.name);
    printf("Pincode: %d\n", o.area.pincode);
    printf("Phone Number: %lld\n", o.ph_no);
    printf("Ordered Items:\n");
    for(int i=0;i<order_count;i++){
        printf("%s x%d\n", o.o_it[i].name, o.o_it[i].quantity);
    }
    printf("Total Cost: %d\n,", sum);
    printf("Estimated Delivery Time: %d minutes\n", max);
    return 0;
}

int main(){
        int rest_count=11;
        struct restaurant r[11];
       

// the above code initializes 5 restaurants with their respective areas, items, prices, and service times. Each restaurant has 5 items in its menu.
// taking user details and order details
        struct order o;
        printf("Enter customer name: ");
        scanf(" %[^\n]", o.customer_name);
        printf("Enter area: ");
        scanf(" %[^\n]", o.area.name);
        printf("Enter area pincode");
        printf("(4400-4404) : ");
        scanf("%d", &o.area.pincode);
        printf("Enter phone number: ");
        scanf("%lld", &o.ph_no);

        //restaurant 1
        strcpy(r[0].name, "ajantha");
        strcpy(r[0].area.name, "lawyerpet");
        r[0].area.pincode = 4400;
        r[0].item_count=5;
        strcpy(r[0].item[0].name, "dosa");
        r[0].item[0].price=50.0;
        r[0].item[0].service_time=10;
        strcpy(r[0].item[1].name, "idli");
        r[0].item[1].price=30.0;
        r[0].item[1].service_time=15;
        strcpy(r[0].item[2].name, "vada");
        r[0].item[2].price=40.0;
        r[0].item[2].service_time=10;
        strcpy(r[0].item[3].name, "upma");
        r[0].item[3].price=35.0;
        r[0].item[3].service_time=25;
        strcpy(r[0].item[4].name, "poha");
        r[0].item[4].price=25.0;
        r[0].item[4].service_time=15;
        r[0].item_count=5;
        strcpy(r[0].item_of_day.name, "kesari");
        r[0].item_of_day.price = 70.0;
        r[0].item_of_day.service_time = 20;
        r[0].spl_item_count=2;
        strcpy(r[0].spl_item[0].name, "chicken biryani");
        r[0].spl_item[0].price = 150.0;
        r[0].spl_item[0].service_time = 30;
        strcpy(r[0].spl_item[1].name, "veg biryani");
        r[0].spl_item[1].price = 200.0;
        r[0].spl_item[1].service_time = 30;


        //restaurant 2
        strcpy(r[1].name, "novotel");
        strcpy(r[1].area.name, "mg road");
        r[1].area.pincode = 4401;
        r[1].item_count = 5;
        strcpy(r[1].item[0].name, "dosa");
        r[1].item[0].price = 45.0;
        r[1].item[0].service_time = 20;
        strcpy(r[1].item[1].name, "poori");
        r[1].item[1].price = 70.0;
        r[1].item[1].service_time = 25;
        strcpy(r[1].item[2].name, "pasta");
        r[1].item[2].price = 120.0;
        r[1].item[2].service_time = 30;
        strcpy(r[1].item[3].name, "salad");
        r[1].item[3].price = 80.0;
        r[1].item[3].service_time = 15;
        strcpy(r[1].item[4].name, "soup");
        r[1].item[4].price = 60.0;
        r[1].item[4].service_time = 10;
        r[1].item_count = 5;
        strcpy(r[1].item_of_day.name, "pongal");
        r[1].item_of_day.price = 120.0;
        r[1].item_of_day.service_time = 30;
        r[1].spl_item_count=2;
        strcpy(r[1].spl_item[0].name, "pulav");
        r[1].spl_item[0].price = 250.0;
        r[1].spl_item[0].service_time = 30;
        strcpy(r[1].spl_item[1].name, "kichidi");
        r[1].spl_item[1].price = 200.0;
        r[1].spl_item[1].service_time = 30;


        //restaurant 3
        strcpy(r[2].name, "ramya");
        strcpy(r[2].area.name, "kanur");
        r[2].area.pincode = 4402;
        r[2].item_count = 5;
        strcpy(r[2].item[0].name, "dosa");
        r[2].item[0].price = 55.0;
        r[2].item[0].service_time = 10;
        strcpy(r[2].item[1].name, "idli");
        r[2].item[1].price = 35.0;
        r[2].item[1].service_time = 15;
        strcpy(r[2].item[2].name, "vada");
        r[2].item[2].price = 45.0;
        r[2].item[2].service_time = 10;
        strcpy(r[2].item[3].name, "roti");
        r[2].item[3].price = 40.0;
        r[2].item[3].service_time = 25;
        strcpy(r[2].item[4].name, "bonda");
        r[2].item[4].price = 30.0;
        r[2].item[4].service_time = 15;
        r[2].item_count = 5;
        strcpy(r[2].item_of_day.name, "curd rice");
        r[2].item_of_day.price = 90.0;
        r[2].item_of_day.service_time = 20;
        r[2].spl_item_count=2;
        strcpy(r[2].spl_item[0].name, "lemon rice");
        r[2].spl_item[0].price = 90.0;
        r[2].spl_item[0].service_time = 20;
        strcpy(r[2].spl_item[1].name, "tomato rice");
        r[2].spl_item[1].price = 80.0;
        r[2].spl_item[1].service_time = 20;


        //restaurant 4
        strcpy(r[3].name, "paradise");
        strcpy(r[3].area.name, "benz circle");
        r[3].area.pincode = 4403;
        r[3].item_count = 5;
        strcpy(r[3].item[0].name, "dosa");
        r[3].item[0].price = 60.0;
        r[3].item[0].service_time = 10;
        strcpy(r[3].item[1].name, "idli");
        r[3].item[1].price = 40.0;
        r[3].item[1].service_time = 15;
        strcpy(r[3].item[2].name, "uthappam");
        r[3].item[2].price = 50.0;
        r[3].item[2].service_time = 10;
        strcpy(r[3].item[3].name, "parota");
        r[3].item[3].price = 45.0;
        r[3].item[3].service_time = 25;
        strcpy(r[3].item[4].name, "poha");
        r[3].item[4].price = 35.0;
        r[3].item[4].service_time = 15;
        r[3].item_count = 5;
        strcpy(r[3].item_of_day.name, "lemon rice");
        r[3].item_of_day.price = 100.0;
        r[3].item_of_day.service_time = 20;
        r[3].spl_item_count=2;
        strcpy(r[3].spl_item[0].name, "zeera rice");
        r[3].spl_item[0].price = 100.0;
        r[3].spl_item[0].service_time = 20;
        strcpy(r[3].spl_item[1].name, "tomato rice");
        r[3].spl_item[1].price = 90.0;
        r[3].spl_item[1].service_time = 20;


         //restaurant 5
        strcpy(r[4].name, "sri sai");
        strcpy(r[4].area.name, "rajiv nagar");
        r[4].area.pincode = 4404;
        r[4].item_count = 5;
        strcpy(r[4].item[0].name, "dosa");
        r[4].item[0].price = 65.0;
        r[4].item[0].service_time = 10;
        strcpy(r[4].item[1].name, "idli");
        r[4].item[1].price = 45.0;
        r[4].item[1].service_time = 15;
        strcpy(r[4].item[2].name, "burger");
        r[4].item[2].price = 55.0;
        r[4].item[2].service_time = 10;
        strcpy(r[4].item[3].name, "chicken biryani");
        r[4].item[3].price = 120.0;
        r[4].item[3].service_time = 30;
        strcpy(r[4].item[4].name, "prawn biryani");
        r[4].item[4].price = 200.0;
        r[4].item[4].service_time = 45;
        r[4].item_count = 5;
        strcpy(r[4].item_of_day.name, "masala dosa");
        r[4].item_of_day.price = 80.0;
        r[4].item_of_day.service_time = 20;
        r[4].spl_item_count=2;
        strcpy(r[4].spl_item[0].name, "vada pav");
        r[4].spl_item[0].price = 50.0;
        r[4].spl_item[0].service_time = 10;
        strcpy(r[4].spl_item[1].name, "pav baji");
        r[4].spl_item[1].price = 30.0;
        r[4].spl_item[1].service_time = 14;
        

        //restaurant 6
            strcpy(r[5].name, "annapurna");
        strcpy(r[5].area.name, "lawyerpet");
        r[5].area.pincode = 4400;   
        r[5].item_count=5;
        strcpy(r[5].item[0].name, "dosa");
        r[5].item[0].price=50.0;
        r[5].item[0].service_time = 10;
        strcpy(r[5].item[1].name, "idli");
        r[5].item[1].price=30.0;
        r[5].item[1].service_time = 15;
        strcpy(r[5].item[2].name, "vada");
        r[5].item[2].price = 40.0;
        r[5].item[2].service_time = 10;
        strcpy(r[5].item[3].name, "upma");
        r[5].item[3].price = 35.0;
        r[5].item[3].service_time = 25;
        strcpy(r[5].item[4].name, "poha");
        r[5].item[4].price = 25.0;
        r[5].item[4].service_time = 15;
        r[5].spl_item_count=2;
        strcpy(r[5].spl_item[0].name, "chicken biryani");
        r[5].spl_item[0].price = 150.0;
        r[5].spl_item[0].service_time = 30;
        strcpy(r[5].spl_item[1].name, "veg biryani");
        r[5].spl_item[1].price = 200.0;
        r[5].spl_item[1].service_time = 30;
        strcpy(r[5].item_of_day.name, "kesari");
        r[5].item_of_day.price = 70.0;
        r[5].item_of_day.service_time = 20;
        
        
        
        //restaurant 7
        strcpy(r[6].name, "mourya");
        strcpy(r[6].area.name, "benz circle");
        r[6].area.pincode = 4403;
        r[6].item_count = 5;
        strcpy(r[6].item[0].name, "dosa");
        r[6].item[0].price = 60.0;
        r[6].item[0].service_time = 10;
        strcpy(r[6].item[1].name, "idli");
        r[6].item[1].price = 40.0;
        r[6].item[1].service_time = 15;
        strcpy(r[6].item[2].name, "uthappam");
        r[6].item[2].price = 50.0;
        r[6].item[2].service_time = 10;
        strcpy(r[6].item[3].name, "parota");
        r[6].item[3].price = 45.0;
        r[6].item[3].service_time = 25;
        strcpy(r[6].item[4].name, "poha");
        r[6].item[4].price = 35.0;
        r[6].item[4].service_time = 15;
        r[6].spl_item_count=2;
        strcpy(r[6].spl_item[0].name, "zeera rice");
        r[6].spl_item[0].price = 100.0;
        r[6].spl_item[0].service_time = 20; 
        strcpy(r[6].spl_item[1].name, "tomato rice");
        r[6].spl_item[1].price = 90.0;
        r[6].spl_item[1].service_time = 20;
        strcpy(r[6].item_of_day.name, "lemon rice");
        r[6].item_of_day.price = 100.0;
        r[6].item_of_day.service_time = 20;
    

        //restaurant 8
        strcpy(r[7].name, "meghana");
        strcpy(r[7].area.name, "mg road");
        r[7].area.pincode = 4401;
        r[7].item_count = 5;
        strcpy(r[7].item[0].name, "dosa");
        r[7].item[0].price = 45.0;
        r[7].item[0].service_time = 20;
        strcpy(r[7].item[1].name, "poori");
        r[7].item[1].price = 70.0;
        r[7].item[1].service_time = 25;
        strcpy(r[7].item[2].name, "pasta");
        r[7].item[2].price = 120.0;
        r[7].item[2].service_time = 30;
        strcpy(r[7].item[3].name, "salad");
        r[7].item[3].price = 80.0;
        r[7].item[3].service_time = 15; 
        strcpy(r[7].item[4].name, "soup");
        r[7].item[4].price = 60.0;
        r[7].item[4].service_time = 10;
        r[7].spl_item_count=2;
        strcpy(r[7].spl_item[0].name, "pulav");
        r[7].spl_item[0].price = 250.0;
        r[7].spl_item[0].service_time = 30;
        strcpy(r[7].spl_item[1].name, "kichidi");
        r[7].spl_item[1].price = 200.0;
        r[7].spl_item[1].service_time = 30;
        strcpy(r[7].item_of_day.name, "pongal");
        r[7].item_of_day.price = 120.0;
        r[7].item_of_day.service_time = 30;
    

        //restaurant 9
        strcpy(r[8].name, "badshah");
        strcpy(r[8].area.name, "kanur");
        r[8].area.pincode = 4402;   
        r[8].item_count = 5;
        strcpy(r[8].item[0].name, "dosa");
        r[8].item[0].price = 55.0;
        r[8].item[0].service_time = 10;
        strcpy(r[8].item[1].name, "idli");
        r[8].item[1].price = 35.0;
        r[8].item[1].service_time = 15;
        strcpy(r[8].item[2].name, "vada");
        r[8].item[2].price = 45.0;
        r[8].item[2].service_time = 10;
        strcpy(r[8].item[3].name, "roti");
        r[8].item[3].price = 40.0;
        r[8].item[3].service_time = 25;
        strcpy(r[8].item[4].name, "bajji");
        r[8].item[4].price = 50.0;
        r[8].item[4].service_time = 20;
        r[8].spl_item_count=2;
        strcpy(r[8].spl_item[0].name, "lemon rice");
        r[8].spl_item[0].price = 90.0;
        r[8].spl_item[0].service_time = 20;
        strcpy(r[8].spl_item[1].name, "tomato rice");
        r[8].spl_item[1].price = 80.0;
        r[8].spl_item[1].service_time = 20;
        strcpy(r[8].item_of_day.name, "curd rice");
        r[8].item_of_day.price = 90.0;
        r[8].item_of_day.service_time = 20;
            
        //restaurant 10
        strcpy(r[9].name, "vijaya");
        strcpy(r[9].area.name, "rajiv nagar");
        r[9].area.pincode = 4404;
        r[9].item_count = 5;
        strcpy(r[9].item[0].name, "dosa");
        r[9].item[0].price = 65.0;
        r[9].item[0].service_time = 10;
        strcpy(r[9].item[1].name, "idli");
        r[9].item[1].price = 45.0;
        r[9].item[1].service_time = 15;
        strcpy(r[9].item[2].name, "burger");
        r[9].item[2].price = 55.0;
        r[9].item[2].service_time = 10;
        strcpy(r[9].item[3].name, "chicken biryani");
        r[9].item[3].price = 120.0;
        r[9].item[3].service_time = 30;
        strcpy(r[9].item[4].name, "methi parata");
        r[9].item[4].price = 60.0;
        r[9].item[4].service_time = 20; 
        r[9].spl_item_count=2;
        strcpy(r[9].spl_item[0].name, "vada pav");
        r[9].spl_item[0].price = 50.0;
        r[9].spl_item[0].service_time = 10;
        strcpy(r[9].spl_item[1].name, "pav baji");
        r[9].spl_item[1].price = 30.0;
        r[9].spl_item[1].service_time = 14;
        strcpy(r[9].item_of_day.name, "masala dosa");
        r[9].item_of_day.price = 80.0;
        r[9].item_of_day.service_time = 20;
    

            //restaurant 11
        strcpy(r[10].name, "sri ram");
        strcpy(r[10].area.name, "rajiv nagar");
        r[10].area.pincode = 4404;
        r[10].item_count = 5;
        strcpy(r[10].item[0].name, "dosa");
        r[10].item[0].price = 65.0;
        r[10].item[0].service_time = 10;
        strcpy(r[10].item[1].name, "idli");
        r[10].item[1].price = 45.0;
        r[10].item[1].service_time = 15;
        strcpy(r[10].item[2].name, "pulihora");
        r[10].item[2].price = 55.0;
        r[10].item[2].service_time = 20;
        strcpy(r[10].item[3].name, "ghee idli");
        r[10].item[3].price = 50.0;
        r[10].item[3].service_time = 15;
        strcpy(r[10].item[4].name, "fried rice");
        r[10].item[4].price = 60.0;
        r[10].item[4].service_time = 20;
        r[10].spl_item_count=2;
        strcpy(r[10].spl_item[0].name, "vada pav");
        r[10].spl_item[0].price = 50.0;
        r[10].spl_item[0].service_time = 10;
        strcpy(r[10].spl_item[1].name, "pav baji");
        r[10].spl_item[1].price = 30.0;
        r[10].spl_item[1].service_time = 14;
        strcpy(r[10].item_of_day.name, "masala dosa");
        r[10].item_of_day.price = 80.0;
        r[10].item_of_day.service_time = 20;
        //setting order count to 0 for all restaurants
        for(int i=0;i<rest_count;i++){
            r[i].order_count = 0;
        }
        int order_count;
        order_count=0;
        sort_restaurants(r, rest_count);
        sort_items_by_name(r, rest_count);
        int k=0;

    while(k==0){
         printf("\n1 : get Min Time\n");
        printf("2 : get Item Availability\n");
        printf("3 : get Item List In Sorted Order\n");
        printf("4 : get Item List Sorted By Price\n");
         printf("5 : get Item List In Area Sorted Order\n");
        printf("6 : get Special Items In Sorted Order\n");
        printf("7 : get Item of Day List in Sorted Order\n");
        printf("8 : get Common Items In Sorted Order\n");
        printf("9 : get Unique Items In Sorted Order\n");
        printf("10 : place order\n");
        printf("11 : add restaurant\n");
        printf("12 : exit\n\n");

        int choice;
         printf("Enter your choice: ");
         scanf("%d",& choice);

        switch(choice){

        case 1:{
            char item_name[20];
            int quantity;

            printf("Enter item name: ");
            scanf(" %[^\n]", item_name);

            printf("Enter quantity: ");
            scanf("%d", &quantity);

            GetMinTime(r, item_name, o.area, quantity, rest_count,0);
            break;
        }
        case 2:{
            char item_name[20];
            printf("Enter item name: ");
            scanf(" %[^\n]", item_name);
            getItemAvailability(r, item_name, rest_count);
            break;
        }
        case 3:{
            char restaurant_name[20];
            printf("Enter restaurant name: ");
            scanf(" %[^\n]", restaurant_name);
            getItemListInSortedOrder(r, rest_count, restaurant_name);
            break;
        }
        case 4:{
            char restaurant_name[20];
            printf("Enter restaurant name: ");
            scanf(" %[^\n]", restaurant_name);
            getItemListSortedByPrice(r, rest_count, restaurant_name);
            break;
        }
        case 5:{
            GetItemListInAreaSortedOrder(r, rest_count, o);
            break;
        }
        case 6:{
            int x;
            printf("Enter number of restaurants in the list : ");
            scanf("%d", &x);
            struct rest_name rn[x];
            for(int i=0;i<x;i++){
                printf("Enter restaurant name %d: ", i+1);
                scanf(" %[^\n]", rn[i].name);
            }
            splitemsinsorted(rn,x,r,rest_count);
            break;
        }
        case 7:{
            GetItemOfDayInSortedorder(r, rest_count);
            break;
        }
        case 8:{
            struct item common_items[MAX_ITEMS];
            int count = GetCommonItemsInSorted(r, rest_count, common_items, 0);
            break;
        }
        case 9:{
            struct item unique_items[MAX_ITEMS];
            int count = GetUniqueItemsInSorted(r, rest_count, unique_items, 0);
            break;
        }
        case 10:{
            int a;
            printf("Enter number of items to order: ");
            scanf("%d", &a);
           
            order_count = a;
            for(int i=0;i<a;i++){
                printf("Enter item name: ");
                scanf(" %[^\n]", o.o_it[i].name);
                printf("Enter quantity: ");
                scanf("%d", &o.o_it[i].quantity);
            }
            placeOrder(r, o, rest_count,order_count);
            k=1;
            
            break;
        }
        case 11:{
            int k;
            k= addRestaurant(r, rest_count);
            rest_count+=k;
            break;
        }
        case 12:{
            k=1;
            break;
        }

        default:
            printf("Invalid choice. Please try again.\n");
    }
}
printf("Thank you for using the food delivery system!\n");
return 0;
}
