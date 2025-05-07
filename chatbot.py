import gradio as gr
from nltk.chat.util import Chat, reflections

# Define improved chatbot logic with corrected patterns
pairs = [
    [r"hi|hello|hey", ["Hello! How can I help you with train booking today?"]],
    [r".*\bbook\b.*", ["Sure! Where would you like to travel from and to?"]],
    [r"from (.*) to (.*)", ["Great! When would you like to travel from %1 to %2?"]],
    [r"on (.*)", ["Noted. How many tickets would you like to book for %1?"]],
    [r"(\d+) tickets?", ["Got it. %1 tickets booked! You'll receive a confirmation soon."]],
    [r"thank you|thanks", ["You're welcome! Have a safe journey."]],
    [r"quit|bye", ["Goodbye! Have a nice day."]],
    [r"hi|hello|hey", ["Hello! How can I help you with train booking today?"]],

    # Booking intent (using synonyms)
    [r".*\b(book|reserve|buy)\b.*", ["Sure! Where would you like to travel from and to?"]],
    
    # Location inputs
    [r"from (.*) to (.*)", ["Great! When would you like to travel from %1 to %2?"]],
    [r"(.*) to (.*)", ["Got it. Please confirm the date you want to travel from %1 to %2."]],
    
    # Date input
    [r"on (.*)", ["Noted. How many tickets would you like to book for %1?"]],
    [r"(today|tomorrow|next week|next month)", ["Thanks. How many tickets would you like to book for %1?"]],
    
    # Ticket count (flexible)
    [r"(\d+) tickets?", ["Got it. %1 tickets booked! You'll receive a confirmation soon."]],
    [r"book (\d+) tickets?", ["Sure, booking %1 tickets. Please hold on..."]],
    [r"(\d+)", ["Booking %1 tickets. Please wait..."]],

    # Class preference
    [r"(sleeper|ac|general|first class)", ["Okay, noted your preference for %1 class."]],

    # Train status
    [r"status of train (.*)", ["Let me check the status of train %1 for you."]],
    [r"is train (.*) on time", ["Checking current status of train %1..."]],

    # Fare inquiries
    [r"fare from (.*) to (.*)", ["Fare varies by class and train. Do you prefer Sleeper or AC?"]],
    [r"how much from (.*) to (.*)", ["Let me check the fare between %1 and %2 for you."]],
    
    # Cancellation
    [r"cancel|cancel ticket|cancel my booking", ["Ticket cancellation request received. Processing..."]],
    
    # Booking confirmation
    [r"confirm", ["Your booking is now confirmed!"]],

    # Modify booking
    [r"change date", ["Sure, what new date would you like to travel?"]],
    [r"change destination", ["Okay, please tell me the new destination."]],
    
    # Thank you & goodbye
    [r"thank you|thanks", ["You're welcome! Have a safe journey."]],
    [r"bye|quit|exit", ["Goodbye! Have a nice day."]],

   
    # New questions
    [r"what trains are available from (.*) to (.*)", ["I can help with that! Please specify your travel date."]],
    [r"what time does the train leave from (.*)", ["The departure time varies. Can you provide the train name or number?"]],
    [r"how much is the fare from (.*) to (.*)", ["Fares vary based on class and train. Would you prefer Sleeper, AC, or General class?"]],
    [r"is there a train from (.*) to (.*) on (.*)", ["Let me check availability from %1 to %2 on %3."]],
    [r"what is the status of train (.*)", ["Please wait while I check the status of train %1."]],
    [r"can I cancel my ticket", ["Yes, tickets can be cancelled. Would you like to proceed with cancellation?"]],
    [r"how can I get a refund", ["Refunds are processed based on the cancellation time and policy."]],
    [r"do you have any discounts", ["There may be discounts for students, senior citizens, and more. Would you like to check eligibility?"]],
    [r"can I book a return ticket", ["Yes, you can book a return ticket. Please specify the return date and time."]],
    [r"what documents are needed for booking", ["A valid ID proof is required during the journey. Booking online just needs your details."]],
    # Trains available - keyword-based
    [r".*\b(train|trains|available)\b.*from (.*) to (.*)", 
     ["I can help with that! Please specify your travel date."]],

    # Train time - flexible input
    [r".*\b(time|when|leave|departure)\b.*from (.*)", 
     ["The departure time varies. Can you provide the train name or number?"]],

    # Fare inquiry
    [r".*\b(fare|cost|price)\b.*from (.*) to (.*)", 
     ["Fares vary based on class and train. Would you prefer Sleeper, AC, or General class?"]],

    # Train availability on date
    [r".*\b(train|available|running)\b.*from (.*) to (.*) on (.*)", 
     ["Let me check availability from %2 to %3 on %4."]],

    # Train status
    [r".*\b(status)\b.*train (.*)", 
     ["Please wait while I check the status of train %2."]],

    # Ticket cancellation
    [r".*\b(cancel|cancellation)\b.*(ticket)?", 
     ["Yes, tickets can be cancelled. Would you like to proceed with cancellation?"]],

    # Refund info
    [r".*\b(refund|money back|reimbursement)\b.*", 
     ["Refunds are processed based on the cancellation time and policy."]],

    # Discounts
    [r".*\b(discount|offer|concession|cheaper)\b.*", 
     ["There may be discounts for students, senior citizens, and more. Would you like to check eligibility?"]],

    # Return ticket
    [r".*\b(return|round trip|back ticket)\b.*", 
     ["Yes, you can book a return ticket. Please specify the return date and time."]],

    # Documents required
    [r".*\b(document|id proof|requirement|paper)\b.*", 
     ["A valid ID proof is required during the journey. Booking online just needs your details."]],
    [r"(.*)", ["I'm not sure I understood. Can you please rephrase that?"]],

     # Fallback
    [r"(.*)", ["I'm not sure I understood. You can try saying 'book ticket', 'Pune to Mumbai', or 'cancel booking'."]],
]


chatbot = Chat(pairs, reflections)

# Define response function
def respond(message, history):
    reply = chatbot.respond(message)
    return reply

# Use ChatInterface for a nice UI
demo = gr.ChatInterface(
    fn=respond,
    title="🚆 Train Booking Bot",
    description="Chat with me to book your train tickets!",
    theme="soft",
)

# Launch the app
demo.launch()



# pip install gradio nltk
# python train_bot.py

