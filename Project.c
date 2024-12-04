#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    char roll_no[10];
    char name[50];
    char department[20];
    char course[10];
    float cgpa;
};

struct node {
    struct node* left;
    struct student data;
    struct node* right
};

struct node* newNode(struct student data) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

struct node* insert(struct node* root, struct student data) {
    if (root == NULL) {
        return newNode(data);
    } else if (strcmp(data.roll_no, root->data.roll_no) < 0) {
        root->left = insert(root->left, data);
    } else if (strcmp(data.roll_no, root->data.roll_no) > 0) {
        root->right = insert(root->right, data);
    } else {
        // Handle duplicate roll numbers (optional)
        printf("Duplicate roll number found!\n");
    }
    return root;
}

void inorderTraversal(struct node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("Roll No: %s\n", root->data.roll_no);
        printf("Name: %s\n", root->data.name);
        printf("Department: %s\n", root->data.department);
        printf("Course: %s\n", root->data.course);
        printf("CGPA: %.2f\n", root->data.cgpa);
        printf("\n");
        inorderTraversal(root->right);
    }
}

struct node* minValueNode(struct node* node) {
    struct node* current = node;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

struct node* deleteNode(struct node* root, char roll_no[10]) {
    if (root == NULL) {
        return root;
    }

    if (strcmp(roll_no, root->data.roll_no) < 0) {
        root->left = deleteNode(root->left, roll_no);
    } else if (strcmp(roll_no, root->data.roll_no) > 0) {
        root->right = deleteNode(root->right, roll_no);
    } else {
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }

        struct node* temp = minValueNode(root->right);
        strcpy(root->data.roll_no, temp->data.roll_no);
        root->right = deleteNode(root->right, temp->data.roll_no);
    }
    return root;
}

struct node* searchByRollNo(struct node* root, char roll_no[10]) {
    if (root == NULL || strcmp(roll_no, root->data.roll_no) == 0) {
        return root;
    }

    if (strcmp(roll_no, root->data.roll_no) < 0) {
        return searchByRollNo(root->left, roll_no);
    } else {
        return searchByRollNo(root->right, roll_no);
    }
}

int main() {
    struct node* root = NULL;

    int choice, found;
    char roll_no[10];
    struct student newStudent;

    while (1) {
        printf("\nStudent Management System\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student by Roll No\n");
        printf("4. Delete Student\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter student details:\n");
                printf("Roll No: ");
                scanf("%s", newStudent.roll_no);
                printf("Name: ");
                scanf(" %[^\n]s", newStudent.name); // Read name with spaces
                printf("Department: ");
                scanf(" %[^\n]s", newStudent.department);
                printf("Course: ");
                scanf(" %[^\n]s", newStudent.course);
                printf("CGPA: ");
                scanf("%f", &newStudent.cgpa);

                root = insert(root, newStudent);
                printf("Student added successfully!\n");
                break;

            case 2:
                if (root == NULL) {
                    printf("No students found!\n");
                } else {
                    printf("\nStudent Records:\n");
                    inorderTraversal(root);
                }
                break;

            case 3:
                printf("Enter student roll number to search: ");
                scanf("%s", roll_no);

                found = (searchByRollNo(root, roll_no) != NULL);
                if (found) {
                    printf("Student Found!\n");
                    // You can further display details from the search result
                } else {
                    printf("Student not found!\n");
                }
                break;

            case 4:
                printf("Enter student roll number to delete: ");
                scanf("%s", roll_no);

                root = deleteNode(root, roll_no);
                if (root != NULL) {
                    printf("Student deleted successfully!\n");
                } else {
                    printf("Student not found!\n");
                }
                break;

            case 5:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}