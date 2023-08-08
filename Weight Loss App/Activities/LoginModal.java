package com.zybooks.weightlosskcl;

public class LoginModal {

    // variables for our login name,
    // contact, email, phone, password.
    private String contactName;
    private String contactEmail;
    private String contactPhoneNumber;
    private String contactPassword;
    private int id;

    // creating getter and setter methods
    public String getContactName() { return contactName; }

    public void setContactName(String contactName)
    {
        this.contactName = contactName;
    }

    public String getContactEmail()
    {
        return contactEmail;
    }

    public void setContactEmail(String contactEmail)
    {
        this.contactEmail = contactEmail;
    }

    public String getContactPhoneNumber() { return contactPhoneNumber; }

    public void setContactPhoneNumber(String contactPhoneNumber)
    {
        this.contactPhoneNumber = contactPhoneNumber;
    }

    public String getContactPassword()
    {
        return contactPassword;
    }

    public void setContactPassword(String contactPassword)
    {
        this.contactPassword = contactPassword;
    }

    public int getId() { return id; }

    public void setId(int id) { this.id = id; }

    // constructor
    public LoginModal(String contactName,
                       String contactEmail,
                       String contactPhoneNumber,
                       String contactPassword)
    {
        this.contactName = contactName;
        this.contactEmail = contactEmail;
        this.contactPhoneNumber = contactPhoneNumber;
        this.contactPassword = contactPassword;
    }
}
