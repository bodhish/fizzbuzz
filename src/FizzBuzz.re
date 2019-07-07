let str = React.string;

type timerId;
[@bs.val] external setTimeout: (unit => unit, int) => timerId = "setTimeout";
[@bs.val] external clearTimeout: timerId => unit = "clearTimeout";

type action =
  | Fizz
  | Buzz
  | FizzBuzz
  | Number;

let fizzbuzz = i =>
  switch (i mod 3, i mod 5) {
  | (0, 0) => FizzBuzz
  | (0, _) => Fizz
  | (_, 0) => Buzz
  | (_, _) => Number
  };

let handleClick = (score, setScore, action, setCountDown) => {
  let correctAnswer = action == fizzbuzz(score);
  setScore(score => correctAnswer ? score + 1 : 1);
  setCountDown(_ => 10);
};

let buttonText = (action, number) =>
  switch (action) {
  | Number => number |> string_of_int
  | Fizz => "Fizz"
  | Buzz => "Buzz"
  | FizzBuzz => "FizzBuzz"
  };

let button = (score, action, setScore, setCountDown) => {
  let text = buttonText(action, score);
  <div
    key=text
    className="bg-green-500 text-white font-bold py-2 px-4 shadow-lg rounded mt-2 py-2 px-4 text-lg text-center "
    onClick={_ => handleClick(score, setScore, action, setCountDown)}>
    {text |> str}
  </div>;
};

let clearTimer = timer => clearTimeout(timer);
let setTimer = (countDown, setCountDown, setScore) => {
  let decriment = () =>
    countDown == 0 ?
      setScore(_ => 1) : setCountDown(countDown => countDown - 1);

  setTimeout(decriment, 1000);
};

[@react.component]
let make = () => {
  let (score, setScore) = React.useState(() => 1);
  let (countDown, setCountDown) = React.useState(() => 10);
  let initialRender = React.useRef(true);

  let timer = setTimer(countDown, setCountDown, setScore);

  React.useEffect1(
    () => {
      timer |> ignore;
      None;
    },
    /* setTimer(countDown, setCountDown); */
    [|countDown|],
  );

  React.useEffect1(
    () => {
      if (initialRender |> React.Ref.current) {
        initialRender->React.Ref.setCurrent(false);
      } else {
        clearTimeout(timer);
      };
      None;
    },
    [|score|],
  );

  <div className="container mx-auto px-2">
    <div className="max-w-md mx-auto">
      <div className="font-bold text-6xl text-center pt-10">
        {"FizzBuzz" |> str}
      </div>
      <div className="font-semibold text-center text-6xl text-green-500">
        {countDown |> string_of_int |> str}
      </div>
      <div className="font-semibold text-center text-6xl text-green-500">
        {score |> string_of_int |> str}
      </div>
      {
        [|Number, Fizz, Buzz, FizzBuzz|]
        |> Array.map(action => button(score, action, setScore, setCountDown))
        |> ReasonReact.array
      }
    </div>
  </div>;
};
