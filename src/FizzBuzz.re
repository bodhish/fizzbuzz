let str = React.string;

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

let handleClick = (setScore, action) =>
  setScore(score => action == fizzbuzz(score) ? score + 1 : 1);

[@react.component]
let make = () => {
  let (score, setScore) = React.useState(() => 1);
  <div>
    <h1> {"FizzBuzz" |> str} </h1>
    <h1> {score |> string_of_int |> str} </h1>
    <div onClick={_ => handleClick(setScore, Number)}>
      {score |> string_of_int |> str}
    </div>
    <div className="bg-blue-500" onClick={_ => handleClick(setScore, Fizz)}>
      {"Fizz" |> str}
    </div>
    <div onClick={_ => handleClick(setScore, Buzz)}> {"Buzz" |> str} </div>
    <div onClick={_ => handleClick(setScore, FizzBuzz)}>
      {"FizzBuzz" |> str}
    </div>
  </div>;
};
