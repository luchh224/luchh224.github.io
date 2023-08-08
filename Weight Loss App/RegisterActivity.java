package com.zybooks.weightlosskcl;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

public class RegisterActivity extends AppCompatActivity {

    //This is going to create variables to edit text, button and dbhandler
    private EditText contactNameEdt, contactEmailEdt, contactPhoneNumberEdt, contactPasswordEdt;
    private DBHandler dbHandler;
    private Button switchToMainActivity;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.register_screen);

        //This is going to initialize our variables. Our edit text views are already assigned names
        //and I will use those on the findViewByID method
        contactNameEdt = findViewById(R.id.editTextName);
        contactEmailEdt = findViewById(R.id.editTextEmail);
        contactPhoneNumberEdt = findViewById(R.id.editTextPhoneNumber);
        contactPasswordEdt = findViewById(R.id.editTextPassword);

        //This will create a dbhandler class and the context will be passed to it
        dbHandler = new DBHandler(RegisterActivity.this);

        switchToMainActivity = findViewById(R.id.button_create_account);
        switchToMainActivity.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                String contactName = contactNameEdt.getText().toString();
                String contactEmail = contactEmailEdt.getText().toString();
                String contactPhoneNumber = contactPhoneNumberEdt.getText().toString();
                String contactPassword = contactPasswordEdt.getText().toString();

                //This will check to see if all of the fields have been filled in
                //and if not, will prompt the user to fill in all of the fields before proceeding
                if (contactName.isEmpty() && contactEmail.isEmpty() && contactPhoneNumber.isEmpty() && contactPassword.isEmpty()) {
                    Toast.makeText(RegisterActivity.this, "Please fill in all of the fields", Toast.LENGTH_SHORT).show();
                    return;
                }

                //This is going to add the new contact and pass the values to the sqlite data
                dbHandler.addNewContact(contactName, contactEmail, contactPhoneNumber, contactPassword);

                //Once the content has been added this message will display to let the user know if is successful
                Toast.makeText(RegisterActivity.this, "Account has been added!", Toast.LENGTH_SHORT).show();
                contactNameEdt.setText("");
                contactEmailEdt.setText("");
                contactPhoneNumberEdt.setText("");
                contactPasswordEdt.setText("");

                startActivity(new Intent(RegisterActivity.this, MainActivity.class));
            }
        });

    }
}
