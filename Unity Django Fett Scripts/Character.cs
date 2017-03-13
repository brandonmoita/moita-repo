using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System;

[RequireComponent(typeof(CharacterController))]
public class Character : MonoBehaviour
{


    public float speed = 6.0f;
    public float jumpSpeed = 8.0f;
    public float rotateSpeed = 5.0f;
    public float gravity = 9.81f;
    Vector3 moveDirection = Vector3.zero;

    public int type = 0;

    private int count;
    public Text countText;

    CharacterController cc;

    public Rigidbody projectilePrefab;
    public Transform projectileSpawnPoint;
    public float fireSpeed = 5.0f;


    /// <summary>
    /// The players current health
    /// </summary>
    private int currentHealth;

    internal void Move(Vector3 desiredVelocity, bool v1, bool v2)
    {
        throw new NotImplementedException();
    }

    /// <summary>
    /// The player's max health
    /// </summary>
    public int maxHealth;

    /// <summary>
    /// The healt's transform, this is used for moving the object
    /// </summary>
    public RectTransform healthTransform;

    /// <summary>
    /// The health text
    /// </summary>
    public Text healthText;

    /// <summary>
    /// The health's image, this is used for color changing
    /// </summary>
    public Image visualHealth;

    /// <summary>
    /// The health's y pos
    /// </summary>
    private float cachedY;

    /// <summary>
    /// The minimum value of the health's x pos
    /// </summary>
    private float minXValue;

    /// <summary>
    /// The max value of the health's x pos
    /// </summary>
    private float maxXValue;

    /// <summary>
    /// The current xValue of the health
    /// </summary>
    private float currentXValue;

    /// <summary>
    /// How often can I take damage
    /// </summary>
    public float cooldown;

    /// <summary>
    /// Indicates if the we can take damage or not
    /// </summary>
    private bool onCD;

    /// <summary>
    /// The healthbar's canvas
    /// </summary>
    public Canvas canvas;


    /// <summary>
    /// Property for accessing the players health
    /// </summary>
    public int Health
    {
        get { return currentHealth; }
        set
        {
            currentHealth = value;
            HandleHealthbar();
        }
    }






    // Use this for initialization
    void Start()
    {
        //Grab a component and keep a reference to it
        cc = GetComponent<CharacterController>();
        if (!cc)
            Debug.Log("CharacterController does not exist.");

        count = 0;
        SetCountText();

        //Sets all start values

        onCD = false;
        cachedY = healthTransform.position.y; //Caches the healthbar's start pos
        maxXValue = healthTransform.position.x; //The max value of the xPos is the start position
        minXValue = healthTransform.position.x - healthTransform.rect.width * canvas.scaleFactor; //The minValue of the xPos is startPos - the width of the bar
        maxHealth = 100;
        currentHealth = maxHealth; //Sets the current healt to the maxHealth



    }

    // Update is called once per frame
    void Update()
    {
        //SimpleMove()
        if (type == 1)
        {
            transform.Rotate(0, Input.GetAxis("Horizontal") * rotateSpeed, 0);

            Vector3 forward = transform.TransformDirection(Vector3.forward);

            float curSpeed = speed * Input.GetAxis("Vertical");

            cc.SimpleMove(forward * curSpeed);
        }
        //Move()
        else if (type == 0)
        {
            if (cc.isGrounded)
            {
                moveDirection = new Vector3(0, 0, Input.GetAxis("Vertical"));

                transform.Rotate(0, Input.GetAxis("Horizontal") * rotateSpeed, 0);

                moveDirection = transform.TransformDirection(moveDirection);

                moveDirection *= speed;

                //jump function

                if (Input.GetButtonDown("Jump"))
                    moveDirection.y = jumpSpeed;

            }

            moveDirection.y -= gravity * Time.deltaTime;

            cc.Move(moveDirection * Time.deltaTime);
        }

        //Key Press Stuff
        if (Input.GetButtonDown("Fire1"))
        {
            
            if (projectilePrefab)
            {
                Rigidbody temp = Instantiate(projectilePrefab, projectileSpawnPoint.position, projectileSpawnPoint.rotation) as Rigidbody;

                temp.AddForce(projectileSpawnPoint.transform.forward * fireSpeed, ForceMode.Impulse);
            }

            
            else
                Debug.Log("No PreFab found");

        }

        

        //Check CollisionFlags on CharacterController
        if (cc.collisionFlags == CollisionFlags.None)
        {
            Debug.Log("Character in air.");
        }

    } //Update


    //Needs Collider Attached to GameObject
    /// <summary>
    /// Handles the healthbar by moving it and changing color
    /// </summary>
    private void HandleHealthbar()
    {
        //Writes the current health in the text field
        healthText.text = "Health: " + currentHealth;

        //Maps the min and max position to the range between 0 and max health
        currentXValue = Map(currentHealth, 0, maxHealth, minXValue, maxXValue);

        //Sets the position of the health to simulate reduction of health
        healthTransform.position = new Vector3(currentXValue, cachedY);

        if (currentHealth > maxHealth / 2) //If we have more than 50% health we use the Green colors
        {
            visualHealth.color = new Color32((byte)Map(currentHealth, maxHealth / 2, maxHealth, 255, 0), 255, 0, 255);
        }
        else //If we have less than 50% health we use the red colors
        {
            visualHealth.color = new Color32(255, (byte)Map(currentHealth, 0, maxHealth / 2, 0, 255), 0, 255);
        }
    }



    void OnTriggerEnter(Collider other)
    {

        if (other.gameObject.tag == "PickUp")
        {
            Destroy(other.gameObject);
            count = count + 50;
            SetCountText();

        }

        if (other.gameObject.tag == "Enemy")
        {
            Health -= 5;
            Debug.Log("Enemy Hit");
        }

        




    }

    void OnTriggerStay(Collider other)
    {
        if (other.tag == "Damage") //Used for simulating taking damage
        {
            if (!onCD && currentHealth > 1)
            {
                StartCoroutine(CoolDownDmg()); //Makes sure that we can't take damage right away
                Health -= 3; //Uses the Health Property to so that we recolor and rescale the health when we change it
            }
        }
        if (other.tag == "Health") //Used for simulating gaining health
        {
            if (!onCD && currentHealth < maxHealth)
            {
                StartCoroutine(CoolDownDmg()); //Makes sure that we can't take damage right away
                Health += 1; //Uses the Health Property to so that we recolor and rescale the health when we change it
            }
        }

        if(Health <= 1)
        {
            Application.LoadLevel("Gameover");
        }
    }

    //void onCollisionEnter()
    //{
    //    Destroy(gameObject);
    //}


    IEnumerator CoolDownDmg()
    {
        onCD = true;
        yield return new WaitForSeconds(cooldown); //Waits a while before we are able to take dmg again
        onCD = false;
    }


    void SetCountText()

    {

        countText.text = "Score: " + count.ToString();

    }

    public float Map(float x, float in_min, float in_max, float out_min, float out_max)
    {
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }
}



