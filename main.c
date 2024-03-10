#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100

struct Product
{
    char name[50];
    int quantity;
    float price;
};

void addProduct(struct Product inventory[], int *numProducts);
void updateProduct(struct Product inventory[], int numProducts);
void deleteProduct(struct Product inventory[], int *numProducts);
void searchProduct(struct Product inventory[], int numProducts);
void displayInventory(struct Product inventory[], int numProducts);
void saveInventory(struct Product inventory[], int numProducts);
void loadInventory(struct Product inventory[], int *numProducts);

int main()
{
    struct Product inventory[MAX_PRODUCTS];
    int numProducts = 0;
    int choice;

    loadInventory(inventory, &numProducts);

    do
    {
        printf("\n===== Inventory Management System =====\n");
        printf("1. Add Product\n");
        printf("2. Update Product\n");
        printf("3. Delete Product\n");
        printf("4. Search Product\n");
        printf("5. Display Inventory\n");
        printf("6. Save Inventory\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addProduct(inventory, &numProducts);
            break;
        case 2:
            updateProduct(inventory, numProducts);
            break;
        case 3:
            deleteProduct(inventory, &numProducts);
            break;
        case 4:
            searchProduct(inventory, numProducts);
            break;
        case 5:
            displayInventory(inventory, numProducts);
            break;
        case 6:
            saveInventory(inventory, numProducts);
            break;
        case 7:
            printf("Exiting program...\n");
            break;
        default:
            printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (choice != 7);

    return 0;
}

void addProduct(struct Product inventory[], int *numProducts)
{
    if (*numProducts >= MAX_PRODUCTS)
    {
        printf("Inventory is full. Cannot add more products.\n");
        return;
    }

    struct Product newProduct;

    printf("Enter product name: ");
    scanf("%s", newProduct.name);

    printf("Enter quantity: ");
    scanf("%d", &newProduct.quantity);

    printf("Enter price: ");
    scanf("%f", &newProduct.price);

    inventory[*numProducts] = newProduct;
    (*numProducts)++;

    printf("Product added successfully.\n");
}

void updateProduct(struct Product inventory[], int numProducts)
{
    char name[50];
    int i;
    int found = 0;

    printf("Enter product name to update: ");
    scanf("%s", name);

    for (i = 0; i < numProducts; i++)
    {
        if (strcmp(inventory[i].name, name) == 0)
        {
            printf("Enter new quantity: ");
            scanf("%d", &inventory[i].quantity);

            printf("Enter new price: ");
            scanf("%f", &inventory[i].price);

            printf("Product updated successfully.\n");
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Product not found.\n");
    }
}

void deleteProduct(struct Product inventory[], int *numProducts)
{
    char name[50];
    int i, j;
    int found = 0;

    printf("Enter product name to delete: ");
    scanf("%s", name);

    for (i = 0; i < *numProducts; i++)
    {
        if (strcmp(inventory[i].name, name) == 0)
        {
            for (j = i; j < *numProducts - 1; j++)
            {
                inventory[j] = inventory[j + 1];
            }
            (*numProducts)--;
            printf("Product deleted successfully.\n");
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Product not found.\n");
    }
}

void searchProduct(struct Product inventory[], int numProducts)
{
    char name[50];
    int i;
    int found = 0;

    printf("Enter product name to search: ");
    scanf("%s", name);

    for (i = 0; i < numProducts; i++)
    {
        if (strcmp(inventory[i].name, name) == 0)
        {
            printf("Product found:\n");
            printf("Name: %s\n", inventory[i].name);
            printf("Quantity: %d\n", inventory[i].quantity);
            printf("Price: %.2f\n", inventory[i].price);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Product not found.\n");
    }
}

void displayInventory(struct Product inventory[], int numProducts)
{
    int i;

    printf("===== Inventory =====\n");
    printf("Name\tQuantity\tPrice\n");
    for (i = 0; i < numProducts; i++)
    {
        printf("%s\t%d\t\t%.2f\n", inventory[i].name, inventory[i].quantity, inventory[i].price);
    }
}

void saveInventory(struct Product inventory[], int numProducts)
{
    FILE *file;
    int i;

    file = fopen("inventory.txt", "w");

    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    for (i = 0; i < numProducts; i++)
    {
        fprintf(file, "%s %d %.2f\n", inventory[i].name, inventory[i].quantity, inventory[i].price);
    }

    fclose(file);
    printf("Inventory saved to file.\n");
}

void loadInventory(struct Product inventory[], int *numProducts)
{
    FILE *file;
    int i;

    file = fopen("inventory.txt", "r");

    if (file == NULL)
    {
        printf("Inventory file not found. Creating new inventory.\n");
        return;
    }

    while (fscanf(file, "%s %d %f", inventory[*numProducts].name, &inventory[*numProducts].quantity, &inventory[*numProducts].price) != EOF)
    {
        (*numProducts)++;
    }

    fclose(file);
    printf("Inventory loaded successfully.\n");
}
